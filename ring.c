#include "ring.h"

void buf_init(void)  //항상 선 실행
{
	int i;
	for (i = 0; i <= buf_size - 1; i++) buf[i] = buf_init_value;			//버퍼 모든값을 초기값(현설정은 0xFF입니다.)으로 설정해준다!
}
void buf_stat(void)		//버퍼 상태를 확인할 수 있다. 출력해준다
{
	int i;
	for (i = 0; i <= buf_size - 1; i++) printf("%X, ", buf[i]);
}
int buf_in(void)		//버퍼에 값을 넣습니다.
{
	int in;		//입력을 받을 변수입니다.
	scanf("%X", &in);    //스캔하고
	if (in == 0xAA) return 1;  //0xAA면 나간다. 데이터 입력받도록 하던지..
	if ((buf_end == buf_size - 1) && (buf[buf_size - 1] == buf_init_value) && (buf[0] != 0xFF))	return 0;	//버퍼의 끝에 있을때 오버플로우 방지 선
	else if ((buf[buf_end] == buf_init_value) && (buf[buf_end + 1] != buf_init_value) && (buf_end != buf_size - 1) && (buf_end != buf_size - 2))	return 0;	//기본오버플로우 방지
	buf[buf_end] = in;    //다른경우에 버퍼에 데이터를 넣는다. 시발	
	buf_end += 1;			//그리고 END값을 1로 증가시켜준다
	if (buf_end >= buf_size) buf_end = 0; //END가 배열 최대값을 초과 하였을시 END를 0으로 초기화 한다.
	return 0;
}
void buf_out(int out)		//시작지점과 종료지점이 같다면 변수를 종료해야 한다. 사전 처리를 해주셔야함		EX) if (buf_start == buf_end)	printf("인출할 데이터가 없습니다.");	
{
	int i;
	for (i = 1; i <= out; i++)
	{
		if (buf[buf_start] == 0xFF) return;
		/*처리*/printf("%X 데이터 on %d번 버퍼\n", buf[buf_start], buf_start);			//데이터를 출력합니다. 아니면 이곳에 다른 출력 like 'UDR == buf[buf_start]를 입력할 수 있습니다. 예)  0xA8 데이터 on 7번 버퍼
		if (buf_start >= buf_size) buf_start = 0;								//buf_start값도 buf_end값처럼 배열 최대값을 초과하면 0으로 초기화 해줍니다. -1을 해주지 않는 이유는 배열[8] 로 설정하였을시 실제 범위는 0~7이기 떄문입니다.
		buf[buf_start] = buf_init_value;				//데이터를 빼낸곳에는 초기값인 0xFF로 초기화해줍니다(위의 #define 참고)
		buf_start += 1;									//데이터를 넣은 후, 1을 증가시켜줌으로 실제 데이터가 시작되는 곳을 다시 가르키게 합니다.
	}		//유아트 할시 데이터 바이트마다 1.5ms의 간격을 주는게 좋습니다. - 혹은 플레그 이용해서 while 쓰는것도 좋은 방법
}
