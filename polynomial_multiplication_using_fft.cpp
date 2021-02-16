/*
In this programme you have to enter polynomials in coefficient form for eg p1=2x^2+x+1 p2=x^3+1 then first enter two numbers m,n where m=degree(p1)+1 n=degree(p2)+1 and then enter m numbers like for p1 1 1 2 and for p2 1 0 0 1

and after entering all data you will get your result like

2x^(5)+1x^(4)+1x^(3)+2x^(2)+1x^(1)+1x^(0)
*/

#include <bits/stdc++.h> 
using namespace std; 

// For storing complex values of nth roots 
// of unity we use complex<double> 
typedef complex<double> cd; 

// Recursive function of FFT 
vector<cd> fft(vector<cd>& a) 
{ 
	int n = a.size(); 

	// if input contains just one element 
	if (n == 1) 
		return vector<cd>(1, a[0]); 

	// For storing n complex nth roots of unity 
	vector<cd> w(n); 
	for (int i = 0; i < n; i++) { 
		double alpha = 2 * M_PI * i / n; 
		w[i] = cd(cos(alpha), sin(alpha)); 
	} 

	vector<cd> A0(n / 2), A1(n / 2); 
	for (int i = 0; i < n / 2; i++) { 

		// even indexed coefficients 
		A0[i] = a[i * 2]; 

		// odd indexed coefficients 
		A1[i] = a[i * 2 + 1]; 
	} 

	// Recursive call for even indexed coefficients 
	vector<cd> y0 = fft(A0); 

	// Recursive call for odd indexed coefficients 
	vector<cd> y1 = fft(A1); 

	// for storing values of y0, y1, y2, ..., yn-1. 
	vector<cd> y(n); 

	for (int k = 0; k < n / 2; k++) { 
		y[k] = y0[k] + w[k] * y1[k]; 
		y[k + n / 2] = y0[k] - w[k] * y1[k]; 
        //cout<<y[k]<<" "<<y[k+n/2]<<endl;
	} 
	return y; 
} 
vector<cd> ifft(vector<cd>& a) 
{ 
	int n = a.size(); 

	// if input contains just one element 
	if (n == 1) 
		return vector<cd>(1, a[0]); 

	// For storing n complex nth roots of unity 
	vector<cd> w(n); 
	for (int i = 0; i < n; i++) { 
		double alpha = -2 * M_PI * i / n; 
		w[i] = cd(cos(alpha), sin(alpha)); 
	} 

	vector<cd> A0(n / 2), A1(n / 2); 
	for (int i = 0; i < n / 2; i++) { 

		// even indexed coefficients 
		A0[i] = a[i * 2]; 

		// odd indexed coefficients 
		A1[i] = a[i * 2 + 1]; 
	} 

	// Recursive call for even indexed coefficients 
	vector<cd> y0 = ifft(A0); 

	// Recursive call for odd indexed coefficients 
	vector<cd> y1 = ifft(A1); 

	// for storing values of y0, y1, y2, ..., yn-1. 
	vector<cd> y(n); 

	for (int k = 0; k < n / 2; k++) { 
		y[k] = y0[k] + w[k] * y1[k]; 
		y[k + n / 2] = y0[k] - w[k] * y1[k]; 
        //cout<<y[k]<<" "<<y[k+n/2]<<endl;
	} 
	return y; 
} 
int convert(double x)
{
    int r=int(x);
    double p=x-double(r);
    //cout<<x<<" "<<p<<endl;
    if(p>.5)
    {
        return r+1;
    }
    if(p<-.5)
    {
        return r-1;
    }
    else{
        return r;
    }
}
int lOg(int x)
{
    int sum=0;
    while(x)
    {
        x/=2;
        sum++;
    }
    return 1<<sum;
}
 vector<int> solve(vector<int> v1,vector<int> v2)
 {
     int m1,m2;
     m1=v1.size();
     m2=v2.size();
     int k=lOg(m1+m2-1);
     //cout<<k<<endl;
     vector<cd> a1(k,0),a2(k,0);
     for(int i=0;i<m1;i++)
     {
         a1[i].real(v1[i]);
     }
     for(int i=0;i<m2;i++)
     {
         a2[i].real(v2[i]);
     }
     vector<cd> b1=fft(a1);
     vector<cd> b2=fft(a2);
     vector<cd> b3;
     for(int i=0;i<k;i++)
     {
         b3.push_back(b1[i]*b2[i]);
         //cout<<b1[i]*b2[i]<<endl;
     }
     vector<cd> ans=ifft(b3);
     double n=double(k);
     vector<int> ans1;
     for(int i=0;i<m1+m2-1;i++)
     {
         ans1.push_back(convert(ans[i].real()/n));
     }
     return ans1;
 }


// Driver code 
int main() 
{ 
    int m,n,x;
    cin>>m>>n;
    vector<int> a,b;
    for(int i=0;i<m;i++)
    {
        cin>>x;
        a.push_back(x);
    }
    for(int i=0;i<n;i++)
    {
        cin>>x;
        b.push_back(x);
    }
    
    vector<int> ans=solve(a,b);
    cout<<endl;
    cout<<ans[ans.size()-1]<<"x^("<<ans.size()-1<<")";
    for(int i=ans.size()-2;i>=0;i--)
    {
        if(ans[i]!=0)
        {
            if(ans[i]<0)
            {
                cout<<ans[i]<<"x^("<<i<<")";
            }
            else{
                cout<<"+"<<ans[i]<<"x^("<<i<<")";
            }
        }
    }
    cout<<endl;
	return 0; 
} 
