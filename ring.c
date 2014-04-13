#include "ring.h"

void buf_init(void)  //�׻� �� ����
{
	int i;
	for (i = 0; i <= buf_size - 1; i++) buf[i] = buf_init_value;			//���� ��簪�� �ʱⰪ(�������� 0xFF�Դϴ�.)���� �������ش�!
}
void buf_stat(void)		//���� ���¸� Ȯ���� �� �ִ�. ������ش�
{
	int i;
	for (i = 0; i <= buf_size - 1; i++) printf("%X, ", buf[i]);
}
int buf_in(void)		//���ۿ� ���� �ֽ��ϴ�.
{
	int in;		//�Է��� ���� �����Դϴ�.
	scanf("%X", &in);    //��ĵ�ϰ�
	if (in == 0xAA) return 1;  //0xAA�� ������. ������ �Է¹޵��� �ϴ���..
	if ((buf_end == buf_size - 1) && (buf[buf_size - 1] == buf_init_value) && (buf[0] != 0xFF))	return 0;	//������ ���� ������ �����÷ο� ���� ��
	else if ((buf[buf_end] == buf_init_value) && (buf[buf_end + 1] != buf_init_value) && (buf_end != buf_size - 1) && (buf_end != buf_size - 2))	return 0;	//�⺻�����÷ο� ����
	buf[buf_end] = in;    //�ٸ���쿡 ���ۿ� �����͸� �ִ´�. �ù�	
	buf_end += 1;			//�׸��� END���� 1�� ���������ش�
	if (buf_end >= buf_size) buf_end = 0; //END�� �迭 �ִ밪�� �ʰ� �Ͽ����� END�� 0���� �ʱ�ȭ �Ѵ�.
	return 0;
}
void buf_out(int out)		//���������� ���������� ���ٸ� ������ �����ؾ� �Ѵ�. ���� ó���� ���ּž���		EX) if (buf_start == buf_end)	printf("������ �����Ͱ� �����ϴ�.");	
{
	int i;
	for (i = 1; i <= out; i++)
	{
		if (buf[buf_start] == 0xFF) return;
		/*ó��*/printf("%X ������ on %d�� ����\n", buf[buf_start], buf_start);			//�����͸� ����մϴ�. �ƴϸ� �̰��� �ٸ� ��� like 'UDR == buf[buf_start]�� �Է��� �� �ֽ��ϴ�. ��)  0xA8 ������ on 7�� ����
		if (buf_start >= buf_size) buf_start = 0;								//buf_start���� buf_end��ó�� �迭 �ִ밪�� �ʰ��ϸ� 0���� �ʱ�ȭ ���ݴϴ�. -1�� ������ �ʴ� ������ �迭[8] �� �����Ͽ����� ���� ������ 0~7�̱� �����Դϴ�.
		buf[buf_start] = buf_init_value;				//�����͸� ���������� �ʱⰪ�� 0xFF�� �ʱ�ȭ���ݴϴ�(���� #define ����)
		buf_start += 1;									//�����͸� ���� ��, 1�� �������������� ���� �����Ͱ� ���۵Ǵ� ���� �ٽ� ����Ű�� �մϴ�.
	}		//����Ʈ �ҽ� ������ ����Ʈ���� 1.5ms�� ������ �ִ°� �����ϴ�. - Ȥ�� �÷��� �̿��ؼ� while ���°͵� ���� ���
}
