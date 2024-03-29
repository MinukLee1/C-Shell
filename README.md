# 1장 쉘 스크립트 개요

### 1.1 UNIX/Linux 소개 및 특징

- 1.1.1 UNIX
    - 1969년 AT&T 벨연구소의 직원이 켄 톰슨, 데니스 리치, 더글라스 매클로리 등이 최초로 개발하였으며, 이후 C언어로 재작성되어 다양한 플랫폼에 이식될 수 있도록 보완되었다.
    - 벨연구소는 대학과 연구기관에 UNIX를 활용할 수 있도록 라이선스를 제공하였으며, 버클리 대학교에서는 UNIX에 네트워크 프로토콜인 TCP/IP 등 다양한 기능을 보강하여 BSD 배포본을 제작하고 이후 파생되는 많은 UNIX에 영향을 끼쳤다.
- 1.1.2 Linux
    - 1991년 리누스 토발즈라는 핀란드 헬싱키 대학의 대학원생에 의해 커널이 개발된 이래, 1984년부터 리처드 스토람에 의해 추진된 GNU 프로젝트의 다양한 소프트웨어들이 합쳐진 운영체제가 Linux이다.
    - 개인용 데스크톱 환경뿐만 아니라 안드로이드 등 스마트폼에서부터 기업용 엔터프라이즈 환경에 이르기까지 다양한 플랫폼에 이식되어 활용중이다.
    - 대표적인 리눅스 배포판에는 데비안, 레드햇, 슬렉웨어, SUSE, 우분투, 젠투가 있으며 그밖에도 다양한 배포본들이 파생되어 개발되고 있다.

### 1.2 쉘의 역할 및 특징

- 쉘은 운영체제에서 커널(Kernel)과 사용자 사이의 인터페이스, 즉 가교 역할을 하는 프로그램으로, 운영체제의 내부 명령어나 응용프로그램을 실행하는 것을 지원한다.
- 시스템을 전체적으로 보면 운영체제는 결국 하드웨어의 한 부분인 저장장치의 일부에 저장된다.
- 운영체제를 좀 더 세부적으로 살펴보면, 운영체제가 설치되어 있는 저장장치(DISK 등)를 비롯하여 모니터, 그래픽카드, NIC 등 시스템에 직간접적으로 연결되는 하드웨어를 통제하는 커널과 이러한 커널과 사용자 및 응용 프로그램 사이에서의 명령을 전달을 담당하는 쉘로 구분할 수 있다.
- 운영체제 마다 기본적으로 다양한 쉘을 제공하고 있고 사용자가 별도의 쉘을 설치해서 활용할 수 있다.
- CDE(Common Desktop Environment)
    - 공통 데스크톱 환경(CDE)은 유닉스를 위한 그래픽 데스크톱 환경이며 모티프 위젯 툴킷을 도입하고 있다.
    - 유닉스 표준화 단체들 가운데 하나인 공통 개방형 소프트웨어 환경이 지정한 유닉스 GUI 규격이다.

### 1.3 쉘의 종류

|구분|개발자|설치 위치|설명|
|:---|:---|:---|:---|
|sh|Stephen Bouren|/bin/sh|대부분의 UNIX 및 Linux에 설치되어 있는 쉘|
|bash|Brain Fox, Chet Ramey|/bin/bash|Linux의 기본 쉘로 sh와 호환|
|ksh|David Korn|/bin/ksh|1980년대 벨연구서에서 개발, 부동 소수점 계산이 가능|
|csh|Bill Joy|/bin/csh|C언어와 비슷한 스타일로 Script를 작성 가능|
|tcsh|Ken Greer|/bin/tcsh|csh에 커맨드 히스토리 등 추가 기능을 보완|

- 쉘 종류의 확인
    ```
    $ ps -p $$
    ```
- /etc/passwd 파일의 내용 중 마지막 필드에 기술된 쉘 경로를 보고 확인할 수 있다.
    ```
    user01:x:500:500::/home/user01:/bin/bash
    ```
- 시스템에 항상 자신이 원하는 쉘이 설치되어 있을 거라고 생각하면 안된다.
- 대부분의 UNIX/Linux 시스템에 기본적으로 설치되어 있는 sh를 중심으로 설명할 것이다.

### 1.4 쉘 스크립트란?

- 컴퓨터 사용의 편의성을 확보한 GUI 기반의 실행 환경인 Windows 초기 버전이 있었지만 DOS를 통해 구동되는 DOS의 확장 프로그램 수준이었기 때문에 일반 사용자가 쉽게 사용하기에는 어려움이 있었다.
- 이러한 번거로움을 조금이나마 해소하고자 DOS 구성 시 메모리 구성 및 드라이버 로딩을 케이스별로 메뉴로 구성하여 케이스별로 선택할 수 있는 배치 파일을 만들어 활용하는 사람들이 있었다.
- 그 당시의 배치 파일을 지금의 쉘 스크립트와 비슷한 개념으로 이해하면 된다.
- 쉘 스크립트 : 운영체제의 쉘에서 사용할 수 있는 명령어를 해석하고 그 결과를 커널에게 전달하는 프로그램
- 쉘 : 사용자가 내린 명령어를 해석하고 그 결과를 커널에게 전달하는 프로그램

### 1.5 쉘 스크립트 활용 시 이점

- 1.5.1 반복 작업에 대한 자동화 기능
    - 쉘 스크립트를 활용하는 가장 큰 장점은 관리자의 번거로움을 덜 수 있다.
    - 스케줄 설정과 같이 주기적으로 수행하는 단순한 작업에 단순한 작업에 쉘 스크립트를 활용하면 관리자가 일일이 타이핑하지 않아도 된다.
- 1.5.2 기존의 명령어를 사용자만의 명령어로 보완
    - 기본적으로 UNIX/Linux는 POSIX라는 표준 규약을 준수하지만 모든 명령어가 통일된 것은 아니기 때문에 운영체제 마다 명령 옵션이나 결과 형식에 약간의 차이가 있다.
    - 운영체제에서 제공하는 명령어 실행 결과를 사용자가 원하는 형식으로 재구성해야 할 때가 있다.
    - 예시
        - 운영체제가 다른 시스템에서 동일한 형태의 로그를 추출해야 할 때가 있다.
        - 이 경우, 쉘 스크립트를 이용하여 기존의 명령어의 결과를 원하는 형태의 결과로 표시할 수 있다.
        - 이를 위해 입출력 재지정(Rdirection)을 활용하면 된다.
- 1.5.3 손쉽고 빠른 개발 및 보완이 가능
    - 기본적으로, 쉘 스크립트 자체는 운영체제의 명령어 등을 묶어서 프로그램화한 후 인터프리터 방식으로 수행되기 때문에 별도의 컴파일러를 설치할 필요가 없다.
    - 운영체제의 명령어들을 잘 알고 있다면 손쉽고 빠른 개발 및 보완이 가능하다.
    - 필요한 절차를 기술하는 것이다.
    - 시스템 관리자가 관리하는 여러 대의 서버 및 원격지에 있는 서버를 설정하거나 패치할 때 쉘 스크립트를 활용하면 설정 및 패치 작업을 보다 더 효율적으로 할 수 있다.
- POSIX(Portable Operating System Interface)
    - 서로 다른 UNIX OS의 공통 API를 정리하여 이식성이 높은 유닉스 응용 프로그램을 개발하기 위한 목적으로 IEEE가 책정한 어플리케이션 인터페이스 규격이다.
    - 대부분의 시스템들이 AT&T에서 개발된 UNIX에 뿌리를 두고 있지만 시간이 흐르면서 다양한 제조사와 개발자의 손을 거치면서 운영체제별 의존성 문제가 발생되었다.
    - POSIX는 운영체제별 의존성 문제를 해결하기 위해 서로 다른 UNIX 운영체제에서 공통 API를 정리하여 운영체제간 이식성이 높은 UNIX 응용 프로그램을 개발하기 위한 목적으로 제정된 API 규격이다.




# 2장 실습 환경 구축

### 2.1 UNIX/Linux 시스템 구축

- 2.1.1 가상머신 설치
    - x86에 설치되지 않는 UNIX/Linux 버전은 사용이 불가능하다.(IMB의 AIX, HP의 HP-UX, SUN의 SPARC CPU 버전 Solaris 등)
    - VMware 또는 VirtualBox 설치
- 2.1.2 게스트 운영체제 설치
    - iso 형식의 운영체제 이미지를 다운로드 받아 설치한다.

    |구분|운영체제/배포본|웹 사이트 주소|
    |:---|:---|:---|
    |UNIX|solaris|[http://www.oracle.com/kr/index.html](http://www.oracle.com/kr/index.html)|
    ||FreeBSD|[http://www.freebsd.org/](http://www.freebsd.org/)|
    ||NetBSD|[http://www.netbsd.org/](http://www.netbsd.org/)|
    ||OpenBSD|[http://www.openbsd.org/](http://www.openbsd.org/)|
    |Linux|ubuntu|[http://www.ubuntu.com/index_roadshow](http://www.ubuntu.com/index_roadshow)|
    ||fedora|[http://getfedora.org/](http://getfedora.org/)|
    ||CentOS|[http://www.centos.org/](http://www.centos.org/)|
    ||KALI linux|[https://www.kali.org/](https://www.kali.org/)|
    ||SUlinux|[https://www.sulinux.net/2014/](https://www.sulinux.net/2014/)|

    - Linux/ubuntu, 메모리 1GB, 가상 하드디스크 8GB(VDI, 동적할당)으로 가상머신을 할당한다.
    - IDE에 우분투 이미지를 넣고 설치를 진행한다.

### 2.2 터미널 접속 환경 구성

- PuTTY를 사용하여 가상머신에 ssh로 접속을 한다.
- PuTTY의 문자를 UTF-8으로 설정한다.

## 2.3 쉘 스크립트 제작 및 수정 환경 구성

- PUTTY를 설치하고 SSH 접속을 통해 시스템에서 제공하는 에디터를 이용해서 쉘 스크립트를 작성할 수 있지만 Windows 환경의 에디터를 활용할 수 있는 방법이 있다.
- 별도의 에디터를 이용하면 코드를 좀 더 가독성 있게 작성 및 분석할 수 있는 이점이 있다.
- [Acroedit](http://www.acrosoft.pe.kr/board/)에서 본인의 PC 환경에 맞는 버전을 다운로드하여 설치한다.
- [파일] 메뉴에서 [FTP]를 클릭하여 [FTP 열기]를 선택하면 창이 나타나는데 좌측 상단의 [계정관리(Alt+A)] 아이콘을 클릭하면 접속할 FTP 정보를 입력하는 창이 나타난다.
- 호스트 PC에서 쉘 스크립트를 작성하고 저장하면 작성된 쉘 스크립트 파일이 가상머신으로 자동으로 전송된다.
- 이때 가상머신의 시스템에서 FTP 서비스가 구동 중이어야 한다.
- FTP 설정이 완료되면 [서버 접속(Alt+E)] 아이콘을 클릭한다. 가상머신의 서버에 접속하여 파일 및 디렉터리 정보를 가져온다.
- 작업할 파일을 선택하면 해당 파일을 불러오고, 여기서 변경 사항을 수정하여 저장하면 서버에 바로 저장된다.
![CustomChell_page-0001](https://user-images.githubusercontent.com/74412438/199155033-20f2dfba-8476-456e-b18c-302d280de1a2.jpg)
![CustomChell_page-0002](https://user-images.githubusercontent.com/74412438/199155054-285dac3a-6e56-4ce6-a89e-f1253f0bd532.jpg)
![CustomChell_page-0003](https://user-images.githubusercontent.com/74412438/199155062-7be458f2-c63c-48d9-a7d7-494d2aa7094e.jpg)
![CustomChell_page-0004](https://user-images.githubusercontent.com/74412438/199155065-f2cd5899-20ec-436b-b74c-1c09402dbae7.jpg)

![CustomChell_page-0005](https://user-images.githubusercontent.com/74412438/199155014-cd0c0235-9142-4ad1-a040-ac0ae929794d.jpg)
![CustomChell_page-0006](https://user-images.githubusercontent.com/74412438/199155079-35e7ebdd-37a2-4eb6-875f-3a796db42a29.jpg)
![CustomChell_page-0007](https://user-images.githubusercontent.com/74412438/199155082-ef9fe2e4-5227-4acc-a909-443d5cc38da1.jpg)
CustomChell_page-0008
![CustomChell_page-0009](https://user-images.githubusercontent.com/74412438/199155095-35870246-570f-4398-9e6d-465c0e551a27.jpg)
![CustomChell_page-0010](https://user-images.githubusercontent.com/74412438/199155106-36175380-1987-4925-8c27-728dc7dfabdd.jpg)
![CustomChell_page-0011](https://user-images.githubusercontent.com/74412438/199155112-58d55b00-2bde-4ee5-aed0-1c48300f765f.jpg)
![CustomChell_page-0012](https://user-images.githubusercontent.com/74412438/199155124-b2f0138a-27a6-433b-80a9-b57552f55b6d.jpg)
![CustomChell_page-0013](https://user-images.githubusercontent.com/74412438/199155133-0653e50c-4789-4223-8261-926c36f76843.jpg)
![CustomChell_page-0015](https://user-images.githubusercontent.com/74412438/199155136-788268e2-76eb-4f05-b663-55b0028e21ed.jpg)
![CustomChell_page-0016](https://user-images.githubusercontent.com/74412438/199155140-63771e1b-6a0b-4a87-8df0-fe0a8f322564.jpg)
![CustomChell_page-0017](https://user-images.githubusercontent.com/74412438/199155155-5dd2f081-e4d4-44ec-9756-8d1745243ac3.jpg)
![CustomChell_page-0018](https://user-images.githubusercontent.com/74412438/199155161-6a22f513-b5dd-4b56-a4b2-e23eb377cdfe.jpg)
![CustomChell_page-0019](https://user-images.githubusercontent.com/74412438/199155167-848605b7-e05d-421e-8de5-022ae01c5d7f.jpg)
![CustomChell_page-0020](https://user-images.githubusercontent.com/74412438/199155172-4266dfa7-e0f0-4a82-941b-a87cd412f086.jpg)
![CustomChell_page-0021](https://user-images.githubusercontent.com/74412438/199155182-e1d30739-ae8b-44be-b978-7395d374fcf4.jpg)
![CustomChell_page-0022](https://user-images.githubusercontent.com/74412438/199155187-319665ce-e61e-4443-a7e3-b208cf4eaf30.jpg)
![CustomChell_page-0023](https://user-images.githubusercontent.com/74412438/199155201-0276aea6-750f-4b79-88a4-b5778a7efb28.jpg)
![CustomChell_page-0024](https://user-images.githubusercontent.com/74412438/199155205-30e1ebe8-a706-4e3a-b294-ec5599a248fb.jpg)
![CustomChell_page-0025](https://user-images.githubusercontent.com/74412438/199155211-961d728a-55fe-41cc-81ca-1ead6c2f7367.jpg)


# 3장 최종 구현 명령어

- cat : 1개 이상의 파일을 화면에 출력
- pwd : 현재 working 디렉토리 출력
- cd  : working 디렉토리 변경
- mkdir : 디렉토리 생성
- ls : 현재 디렉토리에 있는 파일 이름을 출력
- history : 과거 사용된 명령어를 출력
- ![number] -history : 과거 사용된 명령어를 재실행
- ps : 실행중인 process를 출력
- cp : 파일 복사
- rm : 파일 및 디렉토리 삭제
- ln : hard link 작성
- stat : 파일의 status를 출력
- chmod : 파일의 permission을 변경
- alias : 명령어를 alias
- exit : shell 
