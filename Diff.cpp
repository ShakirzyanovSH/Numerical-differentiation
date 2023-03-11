#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

const
	double a = 0.8;
	int n = 13;

double f(double x)
{
	return log(x+1)+x;
}

double df(double x)
{
	return 1/(x+1)+1;
}

double dLagrange(double xk, double *x, double *y) 
{
	double q=0;
	double L=0;
	double s,s2;
	int i,j,k;
	for (i=0;i<n;i++) 
	{
		q=1;
		for (j=0;j<n;j++) if (j!=i) q *= (x[i]-x[j]);
		s=0;
		for (j=0;j<n;j++) 
		{
			s2=1;
			for (k=0;k<n;k++) if (k!=j && k!=i) s2 *= (xk - x[k]);
			if (j!=i) s += s2;
		}
	    L += y[i]/q*s;
    }
	return L;
}


int main()
{
	double h=0.2;
	int k;
	double x[n];
	double y[n];
	double dx[n];
	double dy[n];
	double e[n];

	printf(" Function: f(x) = ln(x+1)+x. Polynomial construction interval [0.8  3] \n");
	printf(" Source mesh \n");
	printf("    x           y    \n");
	
	for(k=0;k<n;k++)
	{
		x[k] = a + k*h;
		y[k] = f(x[k]);
		printf("   %-6.2lf   %-6.2lf \n",x[k],y[k]);		
	}

	printf("\n Numerical differentiation using the Lagrange polynomial \n");
	printf(" Derivative function and error table \n");
	printf("    x           y'        |y' - f'(x)|  \n");
	for(k=0;k<n;k++)
	{
		dx[k] = a + k*h;
		dy[k] = dLagrange(dx[k],x,y);
		e[k] = fabs(dy[k] - df(dx[k]));
		printf("   %-8.4lf   %-8.4lf      %-6.2e \n",dx[k],dy[k],e[k]);		
	}

	getch();
	return 0;
	
}
