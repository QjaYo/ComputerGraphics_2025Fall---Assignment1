# ComputerGraphics_2025Fall---Assignment1

### 핵심 아이디어

1. 체크무늬 평면 구현방법
    - 정점 위치 전달
        - Plain클래스에는 평면의 폭 분할개수를 담는 변수 int div를 둠
        - cpp/updatebuffer()에서 평면의 폭을 div개수로 나누고, 이를 이용해 각 정점의 좌표를 구해 vertices배열에 업데이트함
    - 색상 전달
        - 기본 색을 vec4(0.5f, 0.5f, 0.5f, 1.0f)로 설정함
        - 색 변화량을 2f로 설정함
        - 
        - 위의 수식처럼 (i+j)가 홀수일때와 짝수일때로 나누어서 색상이 교차할 수 있도록 함
        - cpp/updatebuffer()에서 이 색상값을 vertices배열에 업데이트함
    - vertices배열값을 VBO를 통해 glsl으로 전달함
    - 전달한 정점위치와 색상을 통해 그림
2. 파동 구현방법
    - 사인함수를 이용하되, 파동의 중심점에서 멀어질수록 감쇠계수를 곱해 진폭이 작아지도록 구현함
    - 아래는 glsl 에서 파동을 구현할 때 사용한 수식임
        ![image.png](attachment:c79a031c-ceb3-484d-ad4b-624c4c1f09d8:image.png)
        

3. space 입력 처리
- Plain클래스에 bool active 변수를 둠
- h/keyboard()에서 space가 입력되면 plain.active를 toggle함
- h/idle()에서 plain.active = true일때만 g_time을 증가시키도록 함
- g_time은 uniform변수 u_time을 통해 glsl로 넘겨지며, 위에서 언급한 파동함수의 가 됨
- active = false이어서 시간 가 증가하지 않으면 위상변화가 일어나지 않게되어 파동이 멈추게 됨
4. w 입력 처리
    - Plain클래스에 bool wave 변수를 둠
    - h/keyboard()에서 space가 입력되면 plain.wave를 toggle함
    - wave는 uniform변수 plain_wave을 통해 vshader_plain.glsl로 넘겨지며, plain_wave = true일때만 파동 애니메이션을 활성화시키도록 함
5. 1, 2 입력처리
    - Plain클래스에 div 변수를 둠
    - h/keyboard()에서 1,2가 입력되면 plain.modifyDiv() 함수를 통해
        - 1입력 시 div를 1 감소시킴
        - 2입력 시 div를 2 증가시킴
    - plain.cpp/updatebuffer()에서 평면의 폭을 div개수로 나누어 다시 각 정점의 좌표를 구하고, append_square()함수를 통해 vertices배열을 업데이트함

### 시행착오와 해결방안

1. 평면의 모든 부분의 위상차 동일
    1. 문제
        
        ![image.png](attachment:ecc61086-640b-4c3f-b74e-44d34d27f672:image.png)
        
        - 처음 파동을 구현할때는 위와 같이 사인함수 내부에 를 빼주지 않았음
        - 그러자 파동의 모든 지점의 위상이 같아져 버려서 아래 그림과 같은 파동이 만들어졌음
    2. 해결
        
        ![image.png](attachment:a1e7098c-5939-49d4-a93c-65263125733d:image.png)
        
        - 위의 식과 같이 사인함수 입력에 거리에 비례하는 값을 빼줘서 거리에 비례하여 위상차가 발생하도록 하여 해결함
            
            참고로 여기서 k는 파수(단위 길이당 진동수)라고 해석하면 됨
            
2. idle() 함수에서 시간 측정 오차
    1. 문제
        - 수업시간에 배운 sleep()함수를 쓰면 시간 측정 오차가 발생할 뿐더러, 그 시간동안 다른 작업을 하지 못하고 기다리게 되는 문제가 있을 것이라 생각함
        - 시각적으로 지연이 체감이 되진 않았지만 그래도 이보다 더 나은 방법이 있을 것이라 생각함
    2. 해결
        - glutGet(GLUT_ELAPSED_TIME);
        - 위의 함수는 프로그램이 시작되고 지금까지 흐른 시간을 반환하는 함수임
        - 이 함수를 통하면 sleep()을 통해 강제로 프로그램을 멈추지 않고도 idle()함수가 호출된 시간의 간격을 계산하여 시간t 조절이 가능하였음
3. 흐릿한 색깔
    1. 문제
        
        ![image.png](attachment:85d3ceb0-05c9-43f7-b15b-483784cc3d0e:image.png)
        
        - 왼쪽(문제해결전), 오른쪽(문제해결후)
        - 위의 그림과 같이 처음 구현하였을때는 fshader에서
            
            ![image.png](attachment:130c4631-cca2-41c7-8626-65310b7212bf:image.png)
            
            위와 같은 수식으로 색을 정하였는데, 왼쪽 사진처럼 주황/파랑색이 흐릿하게 나왔음
            
        - 앞에 계수를 붙여보니 [-1,1] 구간을 벗어나거나, 전체적으로 주황/파랑색을 띄게 되는 문제가 발생함
    2. 해결
        
        ![image.png](attachment:a3ddb84d-d6a6-4599-bdff-2e4fee95f3f6:image.png)
        
        - 위와 같이 배합비율을 두배하고 [0,1] 구간으로 clamping 했더니 원하는 대로 더 진한 색감이 나왔음
4. 회전행렬 중복 연산
    1. 문제
        - 처음 구현할 때는 vshader 내부에서 회전행렬을 만들어 곱해주었음
        - 하지만 생각해보니 행렬 생성 연산이 각 정점마다 매번 중복된다는 것을 알게됨
        - 평면의 모든 점은 회전 각이 동일하므로, 정점마다 곱해주는 회전행렬이 모두 같음
        - 따라서 셰이더에서 매 정점마다 회전행렬을 각자 계산하여 곱하는건 비효율적임
        - 물론 속도 지연 체감이 되진 않았음
    2. 해결
        - draw()에서 한번만 회전행렬을 계산해준 뒤, 이 행렬을 통째로 uniform 변수로 vshader로 전달하여 중복연산을 최대한 피해보고자 함
5. 추가구현
    - 마우스 스크롤로 확대 및 축소
        
        ![image.png](attachment:e1a18353-c5fc-4af1-b374-caaaccc89a3d:image.png)
        
        - 이번 학기 수강중인 머신비전시스템 과목에서 초점거리와 확대 축소 관계에 대해 배움
        - 머신비전 시스템 강의자료
            
            ![image.png](attachment:59d78758-f582-4517-9ae7-4f775e337014:image.png)
            
        - 이를 활용해 마우스 스크롤 입력을 받아 초점거리 f_len를 조절하여 확대/축소를 구현해봄
        - OpenGL에서 principal point는 항상 정렬되어 있으므로 px, py는 모두 0으로 처리함
        - 또한 아래와 같은 내용을 알게되었음
            
            그래픽스에서는
            
            - Intrinsic Matrix를 Projection Matrix라고 부름
            - Extrinsic Matrix를 View Matrix라고 부름
            - 윗 그림에는 없지만 그래픽스에서는 모델 각각 좌표계가 있어 이를 변환해주는 Model Matrix가 필요함(이 과제에서는 모델좌표계를 도입하지 않아 항등행렬로 처리함)
        - 이 내용을 기반으로초기 정점위치벡터에 Model, View, Projection 행렬을 차례로 곱하여최종 정점위치를 계산하는 방식으로 구현해보았음
    - 마우스 드래그로 평면 회전
        - void mouse(int button, int state, int x, int y);void motion(int x, int y);
        - 위의 두 함수를 통해 마우스 드래그 입력을 받아 x축, z축 회전을 시킴
        - 문제
            
            평면이 정방향일때(z축이 화면의 위를 가리킬때)는
            드래그하는 방향대로 잘 동작하지만
            평면이 반대로 뒤집혔을때(z축이 화면의 아래를 가리킬때)는
            드래그하는 방향의 반대로 움직이는 문제 발생
            
        - 해결
            
            평면의 법선벡터를 구해서 법선벡터가 가리키는 방향이 +y방향일때와 -y방향일때는 나누어 회전을 반대방향으로 처리하였더니 해결됨
