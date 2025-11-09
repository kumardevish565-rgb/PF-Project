#include <stdio.h>
#include <string.h>
char MedicineName[100][30];
int MedicineDetail[100][2],NoOfMedicine;
void AddMedicine(int Id,char Name[],int Quantity){
    int x=0,Flag=0;
    while(x<NoOfMedicine){
        if(MedicineDetail[x][0]==Id){
            Flag=1;
            break;
        }
        x++;
    }
    if(Flag){
        printf("This medicine already exists in the inventory\n");
    }
    else{
        MedicineDetail[NoOfMedicine][0]=Id;
        MedicineDetail[NoOfMedicine][1]=Quantity;
        strcpy(MedicineName[NoOfMedicine],Name);
        NoOfMedicine++;
        printf("New medicine added successfully\n");
    }
}
int main(){
    int id,quantity;
    char name[30];
    printf("Enter \n");
    scanf("%d %s %d",&id,&name,&quantity);
    AddMedicine(id,name,quantity);
}