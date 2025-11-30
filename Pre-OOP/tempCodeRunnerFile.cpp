    int num1, len1=0;
    cout<<"\n Enter a number: ";
    cin>>num1;

    while(num1>0){
        len1++;
        num1=num1/10;
    }

    cout<<"\n Number of digits are: "<<len1;