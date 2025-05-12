#include <all.h>

natl sem_test;
natl max_id;
natq max_i;
natl mutex;
natq num_proc_terminated; 
natl main_sem;
natl sem_test_num;
void hello_body(natq i) 
{
	natq arr[10] = {0};
	for (int i = 0; i < 10000; i++)
	{
		arr[i % 10]++;
	}

	delay(10);
	sem_signal(sem_test);
	terminate_p();
}

void crea_proc(natq)
{
	for (natq i = 1; i <= 65; i++) {
		natl new_id = activate_p(hello_body, i, 4, LIV_UTENTE);
		if (new_id != 0xFFFFFFFF) {
			sem_wait(mutex);
			num_proc_terminated++;
			sem_signal(mutex);
		}
		if (new_id != 0xFFFFFFFF && new_id > max_id) {
			max_id = new_id;
			max_i = i;
		}
	}
	printf("Processi creati: %ld\n", num_proc_terminated);
	for (size_t i = 0; i < num_proc_terminated; i++)
		sem_wait(sem_test);
	sem_signal(main_sem);
	terminate_p();
}

extern "C" void main()
{
	sem_test = sem_ini(0);
	main_sem = sem_ini(0);
	meminfo mi = getmeminfo();

	activate_p(crea_proc, 0, 5, LIV_UTENTE);
	printf("Hello, main\n");
	sem_wait(main_sem);

	meminfo mf = getmeminfo();
	flog(LOG_DEBUG, "Frame liberi inizali: %d", mi.num_frame_liberi);
	flog(LOG_DEBUG, "Heap libero iniziale: %d", mi.heap_libero);

	flog(LOG_DEBUG, "Frame liberi finali: %d", mf.num_frame_liberi);
	flog(LOG_DEBUG, "Heap libero finale: %d", mf.heap_libero);

	terminate_p();
}
