# Week 1 / 1장 멀티스레드(1.1장~1.5장)

## 프로그램(Program)과 프로세스(Process)
- 프로그램 : 컴퓨터에서 실행되는 명령어의 모음이 들어 있는 데이터, Code와 Data로 구성, 디스크에 존재
- 프로세스 : 프로그램이 실행되면 프로그램에 들어있는 명령어가 한줄씩 실행되면서 활동상태가 되는 것, 메모리에 존재

## 스레드
- 프로그램이 실행되는 기본단위
- 프로세스 안에 여러개가 존재(최소 한개 이상 존재)
- 프로세스안의 메모리를 공유
- 스레드마다 스택을 가짐(함수의 로컬 변수들이 스레드마다 존재)
- 스레드는 프로세스에 비해 생성 OverHead가 적음
- 데이터를 공유하기 때문에 캐시미스(cache miss : CPU가 원하는 데이터가 캐시에 없는 상태)가 적음
- 스레드는 프로세스에 비해 통신이 간단

## 스레드의 일생
![01](https://github.com/Han-Ho-Study/ServerStudy/blob/main/한수/server/Image/week1_image1.jpg)

## 운영체제별 스레드 생성 함수
<details>
<summary>코드 접기/펼치기</summary>

```cpp
//윈도우일때
DWORD threadID;
ThreadParam threadParam;
threadParam.value = 123;
CreateThread(
  ...,
  ThreadProc, &threadParam,
  ...,
  &threadID);

//리눅스나 유닉스일때
pthread_t thread;
TrheadParam threadParam;
threadParam.value = 123;
thread_create(&thread, NULL, ThreadProc, &threadParam);

//모던 c++
std::thread t1(ThreadProc, 123);
```
</details>

## 멀티스레드 프로그래밍을 해야하는 상황
1. 오래 걸리는 일 하나와 빨리 끝나는 일 여럿을 같이 해야 할 때
2. 어떤 긴 처리를 진행하는 동안 다른 짧은 일을 처리해야 할 때
3. 기기에 있는 CPU 를 모두 활용해야 할 때

## 컨텍스트 스위치(context switch)
- 여러개의 프로세스가 실행되고 있을 때 기존에 실행되던 프로세스를 중단하고 다른 프로세스를 실행하는 것

## 그외 확인해볼 내용
프로세스 메모리, 스레드 메모리 영역
RAM 메모리 동작 방식 추가
스레드를 관리할때 필요한것 ( 로깅 요소가 무엇이 필요한지 )
Runnable, Blocked 상태는 어떻게 컨트롤하고 알 수 있는가 ( Sleep, I/O )
스레드가 느려지는 이유 ( RAM 메모리, CPU 와 연관시켜서 )
스레드를 느려지게 만들어보기
스레드 옵션중 유용한것 찾아보기
