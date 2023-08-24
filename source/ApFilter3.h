
#ifndef APFILTER3_
#define APFILTER3_

#ifdef __cplusplus
extern "C" {
#endif

// ��������� ��� ������ � ��������
typedef struct APFILTER3 {
	long Input;   // ������� ������
	long Output;  // �������� ������
	long Output1; // ������� ������
	long PrevOut1;// �������� ������
	long Output2; // ������� ������
	long PrevOut2;// �������� ������
	long dt;      // ���������� ������� �������������
	long Tf;      // ���������� ������� �������
	long K1;      // ����������� �������
	long K2;      // ����������� �������
	long PrevOut; // ���������� �������� ��������� �������
} APFILTER3;

void ApFilter3Init(APFILTER3 *);
void ApFilter3Config(APFILTER3 *, long Cutoff, long Value);
void ApFilter3Calc(APFILTER3 *);
void ApFilter3Reset(APFILTER3 *, long Value);

#ifdef __cplusplus
}
#endif // extern "C"

#endif
