#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

struct SCommon
{
	float m_coeff;
	int m_degree;
};
struct SOperations
{
	SCommon m_numerator;
	SCommon m_denomenator;
	SCommon m_result;
	SCommon m_subtractor;
	SCommon m_reminder;
};
SOperations operation[31];

void Initialization()
{
	for (int i = 31; i >= 0; i--)
	{
		operation[i] = { {0, i},{0, i},{0, i},{0, i},{0, i} };
	}
}

void GetData(int max_deg_numerator, int max_deg_denomenator)
{
	printf("\n*coefficients of numerator*\n");
	for (int i = max_deg_numerator; i >= 0; i--)
	{
		printf("Coeff of (X^%d) = ", i);
		scanf("%f", &operation[i].m_numerator.m_coeff);
		operation[i].m_numerator.m_degree = i;
	}

	printf("\n*coefficients of denomenator*\n");
	for (int i = max_deg_denomenator; i >= 0; i--)
	{
		printf("Coeff of (X^%d) = ", i);
		scanf("%f", &operation[i].m_denomenator.m_coeff);
		operation[i].m_denomenator.m_degree = i;
	}
}


void LongDivision(int max_deg_numerator, int max_deg_denomenator)
{
	for (int i = max_deg_numerator; i >= 0; i--)
	{
		operation[i].m_reminder = operation[i].m_numerator;
	}

	for (int i = max_deg_numerator, j = max_deg_denomenator; i >= 0; i--)
	{
		operation[i - j].m_result.m_coeff = operation[i].m_reminder.m_coeff / operation[j].m_denomenator.m_coeff;
		int n = j, k = i;
		while (n >= 0)
		{
			operation[k].m_subtractor.m_coeff = operation[i - j].m_result.m_coeff * operation[n].m_denomenator.m_coeff;
			n--, k--;
		}
		int a = i;
		while (a >= 0)
		{
			operation[a].m_reminder.m_coeff = operation[a].m_reminder.m_coeff - operation[a].m_subtractor.m_coeff;
			a--;
		}
		if (operation[i - 1].m_reminder.m_degree < operation[j].m_denomenator.m_degree) break;
	}
}


void PrintResult(int max_deg_numerator, int max_deg_denomenator)
{
	//-------------------Print Division Result Part-------------------//
	printf("\n\n\nResult = ");
	for (int x = max_deg_numerator - max_deg_denomenator; x >= 0; x--)
	{
		if (x > 1)
			if(operation[x].m_result.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */}
			else if(operation[x].m_result.m_coeff == 1) printf("X^%d", operation[x].m_result.m_degree);
			else printf("%.2f X^%d",operation[x].m_result.m_coeff, operation[x].m_result.m_degree);
		else if (x == 1)
		{
			if (operation[x].m_result.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */}
			else if (operation[x].m_result.m_coeff == 1) printf("X");
			else printf("%.2f X", operation[x].m_result.m_coeff, operation[x].m_result.m_degree);
		}
		else if (x == 0)
		{
			if (operation[x].m_result.m_coeff == 0) {/* Nothing will be printed as the const term = 0 */}
			else printf("%.2f", operation[x].m_result.m_coeff);		
		}
		if (x > 0 && operation[x].m_result.m_coeff != 0) printf(" + ");
	}
	//-------------------Print Reminder Part-------------------//

	/* The first for loop will print the numerator of the reminder
	 *  The Second for loop will print the denomenator of the reminder
	 */

	printf(" + ( ");
	for (int d = max_deg_denomenator - 1; d >= 0; d--)
	{
		if (d > 1)
		{
			if (operation[d].m_reminder.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else if (operation[d].m_reminder.m_coeff == 1) printf("X^%d", operation[d].m_reminder.m_degree);
			else printf("%.2f X^%d", operation[d].m_reminder.m_coeff, operation[d].m_reminder.m_degree);
		}
		else if (d == 1)
		{
			if (operation[d].m_reminder.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else if (operation[d].m_reminder.m_coeff == 1) printf("X");
			else printf("%.2f X", operation[d].m_reminder.m_coeff);
		}
		else if (d == 0)
		{
			if (operation[d].m_reminder.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else printf("%.2f", operation[d].m_reminder.m_coeff);
		}
		if (d > 0 && operation[d].m_reminder.m_coeff != 0) printf(" + ");
		
	}
	printf(" ) / ( ");
	for (int v = max_deg_numerator; v >= 0; v--)
	{
		if (v > 1)
		{
			if (operation[v].m_denomenator.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else if (operation[v].m_denomenator.m_coeff == 1) printf("X^%d", operation[v].m_denomenator.m_degree);
			else printf("%.2f X^%d", operation[v].m_denomenator.m_coeff, operation[v].m_denomenator.m_degree);
		}
		else if (v == 1)
		{
			if (operation[v].m_denomenator.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else if (operation[v].m_denomenator.m_coeff == 1) printf("X");
			else printf("%.2f X", operation[v].m_denomenator.m_coeff, operation[v].m_denomenator.m_degree);
		}
		else if (v == 0)
		{
			if (operation[v].m_denomenator.m_coeff == 0) {/* Nothing will be printed as the coeff = 0 */ }
			else printf("%.2f", operation[v].m_denomenator.m_coeff);
		}
		if (v > 0 && operation[v].m_denomenator.m_coeff != 0) printf(" + ");
		
	}
	printf(" ) \n\n\n");
}

int main()
{
	printf("\t\t\t\t\t***Long Division Programme for Polynomial***\n\n\n");
	int max_degree_numerator, max_degree_denomenator;
	printf("Enter maximum degree of numerator (Don't exceed 30): ");
	scanf("%d", &max_degree_numerator);
	printf("Enter maximum degree of denomenator (Don't exceed 30): ");
	scanf("%d", &max_degree_denomenator);

	Initialization();
	GetData(max_degree_numerator, max_degree_denomenator);
	LongDivision(max_degree_numerator, max_degree_denomenator);
	PrintResult(max_degree_numerator, max_degree_denomenator);
	return 0;
}