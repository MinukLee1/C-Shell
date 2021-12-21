#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAXLINE 64

#include <ctype.h>
#include <fcntl.h>
#define FORMAT "%5s %s\t%8s %s\n" // 각 변수값에 다른 FORMAT 정의

char* cmd_stack[100];
int stack_index;

time_t now;
time_t before;

void history_command(char* str, int type){ // history 명령어를 출력해주는 메서드
	if(type == 1){
		int check = 0;
		int i = stack_index;
		while(check <= 10){
			if(i<=0) break;
				printf("%d.%s\n",i, cmd_stack+i);
				i--; 
				check++;
		}
	}
}


int main(){
	FILE *fp, *cfp; //파일의 포인터명을 선언
	DIR *dir = NULL;
	struct dirent *entry = NULL;
	
	char ch,buf[MAXLINE];

	int i,fd_self,fd;          //프로세스 관련 변수 및 cmd/tty/time/path 값을 저장해줄 배열 선언
	unsigned long time, stime;
	char flag, *tty;
	char cmd1[256], tty_self[256], path[256], time_s[256];

	while(1){
		int str_pointer = 0;
		int cmd_str_pointer = 0;
		int i = 0;
		char cmd[5][50];
		char first[1024];

		char pwd_buf[100];
		getcwd(pwd_buf, 100);
		printf("%s:$ ", pwd_buf);
		
		memset(cmd,0x00,MAXLINE);
		fgets(buf, MAXLINE, stdin);

		while(buf[str_pointer] != '\n'){

			if (buf[str_pointer] == ' '){	
				cmd[i][cmd_str_pointer] = '\0';
				str_pointer++;
				i++;
				cmd_str_pointer = 0;
			} else {
				cmd[i][cmd_str_pointer] = buf[str_pointer];
				str_pointer++;
				cmd_str_pointer++;
			}
		}
		
		strcpy(cmd_stack+(++stack_index), cmd); //입력받은 명령어를 복사해 스택에 저장
		//help
		if (strcmp(cmd[0],"help") == 0){

			printf("Usable command\n");
			printf("cat + filename\n");
			printf("pwd\n");
			printf("cd\n");
			printf("exit\n");
			
		//ls
		} else if (strcmp(cmd[0],"ls") == 0){
			
 			if((dir = opendir(pwd_buf)) == NULL) // 현재디렉터리의 경로를 가져오는데 실패할 경우의 에러처리
			{
				printf("current directory error\n");
			}
			while((entry = readdir(dir)) != NULL) /* 디렉터리 하위에 있는 파일 및 디렉터리의 정보를 하나씩
				                                 읽어와 entry 의 d_name 을  출력 */
			{
				printf("%s\n", entry->d_name);
			}

		//ps
		} else if (strcmp(cmd[0],"ps") == 0){
			
			dir = opendir("/proc"); // 현재 process경로에 접근
			fd_self = open("/proc/self/fd/0", O_RDONLY); // 읽기전용으로 경로를 가져온다
			sprintf(tty_self,"%s",ttyname(fd_self));
			printf(FORMAT,"PID","TTY","TIME","CMD"); // process 정보를 출력할 내용

			while((entry = readdir(dir)) != NULL){ // 경로안의 내용을 하나씩 읽어온다
				flag = 1;
				for(i=0;entry->d_name[i];i++) // entry 구조체에 있는 정보들을 저장
					if(!isdigit(entry->d_name[i])){
						flag = 0;
						break;
					}
				if(flag){
					//process 정보 참조를 위한 경로에 접근
					sprintf(path,"/proc/%s/fd/0",entry->d_name);
					fd = open(path, O_RDONLY);
					tty = ttyname(fd);

					if(tty && strcmp(tty,tty_self) == 0){
						sprintf(path, "/proc/%s/stat", entry->d_name);
						fp = fopen(path,"r");
						fscanf(fp,"%d%s%c%c%c", &i, cmd1, &flag,&flag,&flag);
						cmd1[strlen(cmd1)-1] = '\0';

						// time
						for(i=0;i<11;i++)
							fscanf(fp,"%lu",&time);
							fscanf(fp,"%lu",&stime);
							time = (int)((double)(time+stime)/sysconf(_SC_CLK_TCK));
							sprintf(time_s,"%02lu:%02lu:%02lu",
									(time/3600)%3600,(time/60)%60,time%60); // 초/분/시 출력
							printf(FORMAT,entry->d_name, tty+5, time_s,cmd1+1);
							fclose(fp);
							/* proc/self/fd/ 경로에서 가져온 값들을 순차적으로 출력해준뒤
							   한 프로세스의 출력이 종료되면 flose(fp) */
					}
					close(fd);
				}
			}
			close(fd_self);

		//pwd
		} else if (strcmp(cmd[0],"pwd") == 0){

			char pathname[100]; // 경로명 문자열 배열선언
			char *result = getcwd(pathname,100); // 현재 작업중인 경로를 *result 주소에 저장한다
			if (result == NULL){
				printf("Error: pwd\n"); // 현재 작업중인 경로가 NULL일 경우의 에러처리
			} else{
				printf("%s\n",pathname); // printf로 저장된 경로를 출력해준다
			}

		//history
		} else if (strcmp(cmd[0],"history") == 0){
		
			history_command(cmd[0],1);

		//cd
		} else if (strcmp(cmd[0],"cd") == 0){
		
			int res = chdir(cmd[1]); // chdir함수를 사용해 cmd[1] 의 값을 경로로하여 위치를  이동해준다
			if (res == -1){ // 경로가 존재하지 않을 경우의 에러 처리
				printf("%s: No such file or directory\n",cmd[1]);
			}

		//mkdir
		} else if (strcmp(cmd[0],"mkdir") == 0){
			
			int res  = mkdir(cmd[1], 0776); // rwxrwxrw- 의 파일권한을 가진 디렉터리를 생성
			if (res == -1){ // 같은 이름의 디렉토리가 있을경우의 에러 처리
				printf("%s: Such directory already exist\n", cmd[1]);
			} else { // 디렉토리 생성 성공 메시지
				printf("Successfully created directory %s\n", cmd[1]);
			}

		//rm
		} else if (strcmp(cmd[0],"rm") == 0){

			int res = remove(cmd[1]); // 받아온 파일을 remove 함수를 사용하여 삭제
			if (res == -1){ // 삭제 실패시 에러처리
				printf("%s: No exist file or directory\n", cmd[1]);
			} else { // 성공 메시지
				printf("Successfully removed file %s\n", cmd[1]);	
			}

		//chmod
		} else if (strcmp(cmd[0],"chmod") == 0){
			
			char *filename = ("%s\n", cmd[1]); // 변경할 파일이나 디렉터리를 포인터주소에 저장
			int a;
			sscanf(cmd[2],"%o",&a); // 8진수로 변환하여 출력해준다

			int res = chmod(filename, a); // chmod함수를 사용하여 권한을 변경해준다

			if (res == -1){ // 에러처리
				printf("Failed change file mode!\n");
			}
			else{ // 성공 메시지
			printf("Succeed change file mode\n");
			}

		//cat
		} else if (strcmp(cmd[0],"cat") == 0){
		
			for(i=1;i<4;i++){
			char *filename = ("%s\n",cmd[i]); // filename포인터주소에 명령어값을 저장
			fp = fopen(filename, "r"); // 파일 오픈
			if (fp == NULL){
				printf("Can't open %s\n", filename); // 에러처리
			}else{
			while(fgets(buf, 255, fp) != NULL){
				printf("%s", buf);          //파일출력
				}
				fclose(fp);	
			}
			}

		//cp		
		} else if (strcmp(cmd[0],"cp") == 0){
		
			char *filename =  ("%s\n", cmd[1]); //cmd[1]을 통해 받은 문자열을 포인터 주소값으로 저장
			fp = fopen(filename, "r"); // 파일을 읽기용으로 open
	
			char *cfilename = ("%s\n", cmd[2]); //cmd[2]을 통해 받은 문자열을 포인터 주소값으로 저장
			cfp = fopen(cfilename, "w"); // 파일을 쓰기용으로 open
		
			if (fp == NULL){ //파일을 여는데 실패할 경우의 에러처리
				printf("Can't open file or directory\n");
			} else {
				while (1){
					ch = fgetc(fp); //fp변수에서 파일을 내용을 한글자씩 읽어온다
					if(ch == EOF){ //에러처리
					break;
					}
					else{
					fputc(ch, cfp); // cfp에 받아온 문자를 하나씩 넣어준다
					}
				}
			fclose(fp); //파일닫아주기
			fclose(cfp);
			printf("File %s copied successfully in the file %s\n\n",filename,cfilename); //성공메시지
			}

		//stat
		} else if (strcmp(cmd[0],"stat") == 0){
			
			struct stat buf; // 구조체 선언
			stat(cmd[1], &buf); //stat함수에서 구조체 buf의 값들을 받아온다

			printf("File type: "); //파일에 상태에 따른 파일타입을 출력
			switch (buf.st_mode & S_IFMT){
				case S_IFBLK: printf("Block device\n"); break;
				case S_IFCHR: printf("Character device\n"); break;
				case S_IFDIR: printf("Directory file\n"); break;
				case S_IFIFO: printf("FIFO/pipe\n"); break;
				case S_IFLNK: printf("Symlink\n"); break;
				case S_IFREG: printf("Regular file\n"); break;
				case S_IFSOCK: printf("Socket\n"); break;
				default: printf("Unknown file\n"); break;
			}
			// 파일 각각의 정보를 출력해준다
			printf("I-node number		  %ld\n", (long) buf.st_ino);
			printf("Mode      		  %lo (octal) \n", (unsigned long) buf.st_mode);
			printf("Link count                %ld\n", (long) buf.st_nlink);
			printf("Ownership          	  UID=%ld GID=%ld\n", (long) buf.st_uid,(long) buf.st_gid);
			printf("Preferred I/O block size  %ld bytes\n", (long) buf.st_blksize);
			printf("File size:                %lld bytes\n", (long long) buf.st_size);
			printf("Blocks allocated       	  %lld\n", (long long) buf.st_blocks);
			printf("Last status change        %s", ctime(&buf.st_ctime));
			printf("Last file access          %s", ctime(&buf.st_atime));
			printf("Last file modification    %s", ctime(&buf.st_mtime));

		//ln
		} else if (strcmp(cmd[0],"ln") == 0){

			int l = link(cmd[1], cmd[2]); // link함수를 사용하여 하드링크 파일을 생성해준다

			if(l == -1){ // 에러처리
				printf("Failed Hard Link created\n");
			}
			else {
				printf("Hard Link created successfully\n");
			}

		//exit	
		} else if (strcmp(cmd[0],"exit") == 0){
			break; //쉘을 종료하고 빠져나온다

		} else {
			printf("Command %s is not found\n",cmd[0]);
		}
	}
}
				

