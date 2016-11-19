##Gainput Library 사용방법

JoyStick API 관련은 다음을 참조 : <br>
https://github.com/highfence/JoyStick_Prototype <br> <br>

###1.
프로젝트 속성 -> C/C++ -> 추가포함 디렉터리 <br>
폴더 아이콘을 눌러 새로운 디렉터리를 추가 <br>
같이 올라간 Gainput/lib/include를 지정 <br>

###2.
프로젝트 속성 -> 링커 -> 추가 라이브러리 디렉터리 <br>
Gainput/Debug 지정 <br> <br>

###3.
프로젝트 속성 -> 링커 -> 입력 -> 추가 종속성 <br>
폴더 아이콘을 눌러 새로운 라이브러리 파일을 사용해준다. <br>
gainputstatic.lib 입력 <br> <br>


현재 gainput폴더 전체 용량이 300mb정도 되는데, 그 중에서 추리고 추려서 대략 13mb정도 올라가 있습니다. <br>
필요없는 부분을 다 없애 버렸다고 생각을 하지만 사용도중 문제가 생길 경우 추가적으로 필요한 파일을 찾아 올리겠습니다. <br>
