#include <gmp.h>
#include <stdio.h>
#include <iostream>
#include <gmpxx.h>
using namespace std;

const int MAX_ITERATIONS = 50000;
const int PRECISION = 8192 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2 * 2;

void fact(mpf_t& f, int num)
{
	mpf_set_default_prec(PRECISION);
	mpf_set_ui(f, 1);
	if (num == 0)
	{
		mpf_set_ui(f, 1);
		return;
	}
	for(int i = 1; i <= num; i++)
	{
		mpf_mul_ui(f, f, i);
	}
	return;
}

void euler(mpf_t &e)
{
	mpf_set_default_prec(PRECISION);
	mpf_t term, f;
	mpf_init(term);
	mpf_init(f);
	for(int i = 0; i <= MAX_ITERATIONS; i++)
	{
		fact(f, i);
		mpf_set_ui(term, 1);
		mpf_div(term, term, f);
		mpf_add(e, e, term);
		cout << i << " itr" << endl;
	}
	mpf_clear(f);
	mpf_clear(term);
	return;
}

int main()
{
	FILE * out;
	out = fopen("out.txt","w");
	mpf_set_default_prec(PRECISION);
	mpf_t e;
	mpf_init(e);
	mpf_set_ui(e, 0);
	euler(e);
	gmp_printf("e: %F.f\n",e);
	gmp_fprintf(out,"%F.f\n",e);
	mpf_clear(e);
	fclose(out);
	return 0;
}
