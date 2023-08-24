
#ifndef APFILTER3_
#define APFILTER3_

#ifdef __cplusplus
extern "C" {
#endif

// Структура для работы с фильтром
typedef struct APFILTER3 {
	long Input;   // Входной сигнал
	long Output;  // Выходной сигнал
	long Output1; // Входной сигнал
	long PrevOut1;// Выходной сигнал
	long Output2; // Входной сигнал
	long PrevOut2;// Выходной сигнал
	long dt;      // Постоянная времени семплирования
	long Tf;      // Постоянная времени фильтра
	long K1;      // Коэффициент фильтра
	long K2;      // Коэффициент фильтра
	long PrevOut; // Предыдущее значение выходного сигнала
} APFILTER3;

void ApFilter3Init(APFILTER3 *);
void ApFilter3Config(APFILTER3 *, long Cutoff, long Value);
void ApFilter3Calc(APFILTER3 *);
void ApFilter3Reset(APFILTER3 *, long Value);

#ifdef __cplusplus
}
#endif // extern "C"

#endif
