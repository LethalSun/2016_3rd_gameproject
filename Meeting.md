##16.11.10 회의

###1.	맵 구상 <br>

  -	STAGE 1 전체 맵의 크기 : 3개의 맵으로 구성 <br> <br>
  -	MAP 1 : <br>
    몹 1 리소스(Choco), 몹 2 리소스(Atroce) <br>
    https://drive.google.com/file/d/0BxzeUSJe9TjVWVY5bjdPUEZCd0k/view <br>

  -	MAP 2 : <br>
    등장 몹 - 맵 1의 몹 타입 2-1과 원거리 공격 몹 3-1, 3-2를 추가. (리소스 Archer_Skeleton) 몹 3-2는 원거리 공격을 맞았을 시, 밀림이나 경직등의 상태이상. <br>
    중간보스(리소스 Acient Tree) – 등장 몹을 전부 죽였을 경우 생성. <br>
    구체적인 기획은 맵 1 구현이 끝난 후 <br> 

  -	MAP 3 : <br>
    보스 – 광역, 몹 소환, 직접공격등의 패턴. <br>

###2.	스킬 구상  <br>

  -	우선 공격/방어에 해당하는 스킬 1개씩 먼저 구현하기.
  -	MAP 1, MAP 2에서 스킬 한 개 씩을 배울 수 있도록.
  -	공격 스킬 : WARCRAFT 3의 스톰볼트 (투사체, 몬스터 경직)
  -	방어 스킬 : WARCRAFT 3의 아바타 (체력 뻥튀기, 안밀리기)
  -	추가적으로 전광석화(빠르게 움직여서 밀쳐내기) 이런 거는 만들기 쉬울 듯.

###3.	큰 일정 <br>

  전체 개발 기간 7주 <br>
  1~2 Week : MAP 1 타일 구현. 몹1, 몹 2-1, 2-2 AI, 첫 번째 스킬, 캐릭터 이동 구현. <br>
  2~3 Week : MAP 2, 중간보스, 몹 3 AI, 두 번째 스킬 구현. <br>
  5~6 Week : MAP 3, 보스 AI 구현 <br>
  7~ Week : 디테일, 디버깅 <br>

###4.	세부 일정 <br>

  이번 주말 : 리소스 스프라이트 작업. <br>
  Week 1 목표 : MAP 1 타일, 몹 1, 2 AI. MAP 1, MAP 2간 이동 구현. <br>

  -	분업 : <br>
  	김현우 : 수요일까지 공격 구현. 이후 다른 쪽 헬프 <br>
  	고금성 : MAP 1 타일, 맵 간 이동. <br>
  	이근원 : AI <br>
  + GAINPUT LIB 설치/실험 ( 조이스틱 인풋 라이브러리 ) <br>

	Week 2 목표 : 첫 번째 스킬(스톰볼트) 구현, 메인 페이지 만들기, 몹 피격 / 공격 확인.


## 16.11.14

### 수요일까지 :<br>
 나 - AI 완성<br>
 금성이형 - 맵 이동 구현<br>
 현우형 - HP 구현(한 번에가 아니라 몇 대 맞아서 죽을 수 있는지.)<br>


 중간보스는 크기 두배. <br>

 몹 위치 정하기 - 구체적으로(좌표까지)<br>

 맵 1 첫 번째 길 - 32 * 7 픽셀<br>
 길은 아래 32 * 8칸 위부터 맵의 중간(높이)까지.<br>
 너비는 전체의 1/5 - 32 * 20칸.<br>
 
 Choco를 잡은 뒤, 바로 몹2를 상대.<br>
 몹 2 뒤에는 바로 돌을 배치해서, 플레이어가 위나 아래로 돌아가서 몹 2-1(무리)을 인식할 수 있도록 배치.<br>

 그 뒤에 전진하게 될 경우 몹2-1 두 마리를 상대하는 경우가 발생할 수 있도록 두 마리가 한 화면에 나오는 경우가 발생할 수 있게 배치.<br>


 몹2-1 배치는 어떻게 할 것인지?<br>
 - Choco 두 마리랑 늑대 한 마리가 있는데, 삼각형으로 젠을 시킬거다. 늑대가 뒤에 있는 삼각형으로 젠을 시킨다.  돌 위에 있는 친구들만, 배치를 위아래로 하도록.<br>
 
 
 
 
 <br>
 ## 16.11.23
 
 ![Alt text](/IDCA/Resources/Data/PngForGithub/GameStructure.png?raw=true "GameStructure")
 
 <br>





Input 을 따로 떼어 놓는다 <br>

InputLayer ->  <br>


SceneUpdate (  <br>

    InputLayer -> 입력 값을 받는다.  (싱글톤) <br>

    Manager -> ChangeState		 <br>

    Player -> Move ( <br>

		if (is지형과의 충돌) <br>

    
    .... <br>

    .... <br>

) <br>


플레이어는 PlayerState를 가지고 있는다. CharacterManager는 Player의 state가 어떻게 되야하는지를 계산하여 Player의 State를 바꿔준다. <br>

PlayerState : IDLE, WALKING, ATTACKING; <br>




CollideManager 모든 객체 ( Player, Enemy, 투사체 )를 포인터로 들고 있는다. <br>

-> 충돌판정이 나면, 투사체는 죽고, 해당하는 매니저에게  <br>




방향키 <br>
Q, W, E -> 공격, 스킬1, 스킬 2 <br>
ESC -> 메뉴 <br>


조이패드<br>
스틱 입력 -> 방향<br>
A, B, X  -> 공격, 스킬 1, 스킬 2<br>
START -> 메뉴<br>


byte 배열 -> idx는 enum으로.<br>

old byte배열<br>
cur byte배열<br>
-> 상태 byte배열.<br>


Move -> 캐릭터가 소유<br>
맵 관리자에게 현재 위치를 주고<br>
갈 수 있다면 이동.<br>
아니라면 스킵.<br>


//Player info<br>
Hp<br>
MaxHp<br>
Mp<br>
MaxMp<br>
이동속도<br>
공격/ 방어력<br>

충돌 태그<br>
피격 범위 계산 _> Collide에서 읽을 수 있게.<br>


상태 이상은 -> 따로 빼서 함수로 처리.<br>
이상상태 업데이트를 하나 준비해서, 이상상태일때만 업데이트.<br>


SkillBase <br>
{
    virtual Action;
    ...
}<br>

플레이어는 함수 포인터 슬롯을 가지고 있어서 넣었다 뺐다만 할 수 있도록.<br>


