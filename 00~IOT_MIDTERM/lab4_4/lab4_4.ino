int i,j,k,l,n = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()){
    n=Serial.parseInt();    // j is horizontal
    Serial.print("n = "); // i is vartical
    Serial.println(n);
    for(i=0;i<=n;i++){
      Serial.println();
        for(l=n-i;l>=0;l--){Serial.print(" ");}
        for(j=0;j<=i;j++){Serial.print(j);}
        for(k=i-1;k>=0;k--){Serial.print(k);}
    }
    for(i=n-1;i>=0;i--){
      Serial.println();
        for(l=n-i;l>=0;l--){Serial.print(" ");}
        for(j=0;j<=i;j++){Serial.print(j);}
        for(k=i-1;k>=0;k--){Serial.print(k);}
    }
  }
}
