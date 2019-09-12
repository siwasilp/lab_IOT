int i,j,k;
void setup() {
  Serial.begin(115200);
}

void loop() {
   while(Serial.available()>0){
    int num = Serial.parseInt();
       
       for(i=1;i<=num;i++){
        Serial.println();
        for(j=1;j<=num;j++){
          if(i==1||i==num||j==1||j==num){
             Serial.print(j);
             Serial.print(" ");
            }
          else if(j==i||j==num-i){
            //j==i||j==num-i
               Serial.print("x ");
            }
          else{
            Serial.print("  ");
          }
        }
      }
     
   }
}
