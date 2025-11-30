    int arr1[5];
    cout<<"Enter 5 numbers";

    for(int i =0; i<5; i++){
        cout<<"\nEnter number "<<i+1<<" :";
        cin>>arr1[i];
    }

    int lar = 0, seclar=0;
    for(int i=0; i<5; i++){
        
        if(lar<arr1[i]){
            lar = arr1[i];
        } else {
            if(seclar<arr1[i]){
                seclar = arr1[i];
            }
            
        }
    }

    cout<<"Largest number is: "<<lar;
    cout<<"\nSecond largest number is: "<<seclar;