#define buf_size 15        //���� ������
#define buf_startpoint 5      //���� ���� ���� ����
#define buf_init_value 0xFF       //���� �⺻ �� 0xFF
unsigned char buf[buf_size];      //���� ���� �� ������ ����
unsigned char buf_start = buf_startpoint;   //START ������ buf_startpoint
unsigned char buf_end = buf_startpoint;    //END ������ buf_startpoint

void buf_init(void);
void buf_stat(void);
int buf_in(void);
void buf_out(int out);
