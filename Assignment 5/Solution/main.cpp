#include <iostream>
#include "SmartString.h"

using namespace std;

int main()
{
    char tempA[] = "Habib ";
    char* temp1 = tempA;
    char tempB[] = "University ";
    char* temp2 = tempB;
    char tempC[] = "Dr. Umair ";
    char* temp3 = tempC;
    char tempD[] = "OOP ";
    char* temp4 = tempD;

    SmartString s;
    SmartString t;
    SmartString s1(temp1);
    SmartString s2(temp2);

    s.Join(temp3);
    cout<<"s.Join(temp3) gives the value of s: "<<endl;
    s.Show();

    s.Join(s1);
    cout<<"\ns.Join(s1) gives the value of s: "<<endl;
    s.Show();

    t.Join(s2);
    cout<<"\nt.Join(s2) gives the value of t: "<<endl;
    t.Show();

    cout<<"\nSmartString Initialized, s1: "<<endl;
    s1.Show();
    cout<<"\nSmartString Initialized, s2: "<<endl;
    s2.Show();

    SmartString s3(s2);
    cout<<"\nSmartString s3(s2) gives the value of s3: "<<endl;
    s3.Show();

    s1.Join(s2);
    cout<<"\ns1.Join(s2) gives the value of s1: "<<endl;
    s1.Show();

    SmartString s4 = s1 + s2;
    cout<<"\ns4 = s1 + s2 gives the value of s4: "<<endl;
    s4.Show();

    SmartString s5 = s1 + temp3;
    cout<<"\ns5 = s1 + temp3 gives the value of s5: "<<endl;
    s5.Show();

    s3 = s1 + s2 + s3;
    cout<<"\ns3 = s1 + s2 + s3 gives the value of s3: "<<endl;
    s3.Show();

    s1+=s2;
    cout<<"\ns1+=s2 gives the value of s1: "<<endl;
    s1.Show();

    cout<<"\nCurrent value of s2 is: "<<endl;
    s2.Show();

    s2 = s1;
    cout<<"\ns2 = s1 gives the value of s2: "<<endl;
    s2.Show();

    bool cond = false;
    if (s1==s2)
        cond = true;
    cout<<"\nThe two SmartStrings s1 and s2 are equal: "<<cond<<endl;

    s1+=s2+=s3+=temp2;
    cout<<"\ns1+=s2+=s3+=s4 give the value of s1: "<<endl;
    s1.Show();

    s1+=s2+=s3=s4=temp1;
    cout<<"\ns1+=s2+=s3=s4 gives the value of s1: "<<endl;
    s1.Show();


    delete temp1;
    delete temp2;
    delete temp3;
    delete temp4;
}
