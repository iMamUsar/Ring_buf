#define buf_size 15        //버퍼 사이즈
#define buf_startpoint 5      //버퍼 임의 시작 지점
#define buf_init_value 0xFF       //버퍼 기본 값 0xFF
unsigned char buf[buf_size];      //버퍼 선언 및 사이즈 설정
unsigned char buf_start = buf_startpoint;   //START 지점은 buf_startpoint
unsigned char buf_end = buf_startpoint;    //END 지점도 buf_startpoint

void buf_init(void);
void buf_stat(void);
int buf_in(void);
void buf_out(int out);
