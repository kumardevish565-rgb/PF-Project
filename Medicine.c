#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define size 100
int ValidateId(int id){ //Checks if Id is valid
    if(id<0){
        printf("Invalid Id\n");
        return 0;
    }
    else
        return 1;
}
int ValidateName(char name[]){  //Checks if medicine name is valid
    int flag=1;
    for(int a=0;name[a]!='\0';a++){
        if(!isalpha(name[a])){
            flag=0;
            break;
        }
    }
    if(!flag)
        printf("Medicine name can only contain alphabhets\n");
    return flag;
}
int ValidateQuantity(int quantity){ //Checks if quantity is valid
    if(quantity<0){
            printf("Quantity cannot be less than zero\n");
            return 0;    
    }
    else
        return 1;
}
void AddMedicine(char MedicineName[][31],int MedicineDetail[][2],int *ptr){
    if(*ptr>size-1) //Check if Inventory is full
        printf("Inventory is full\n");
    else{
        int Id;
        do{
            printf("Enter medicine Id \n");
            scanf("%d",&Id);
        }while(!ValidateId(Id));    //Validates user input of Id
        int Flag=0,x=0;
        while(x<*ptr){  //Prevent duplication of same medicine
            if(MedicineDetail[x][0]==Id){
                Flag=1;
                break;
            }
            x++;
        }
        if(Flag==1)
            printf("This medicine already exists in the inventory\n");
        else{
            int Quantity;
            char Name[30];
            scanf("%*c");
            do{
                printf("Enter medicine name.It cannot be more than 30 characters \n");
                scanf("%30s",Name);
            }while(!ValidateName(Name));    //Validates user input of medicine name
            scanf("%*c");
            do{
                printf("Enter quantity of the medicine \n");
                scanf("%d",&Quantity);
            }while(!ValidateQuantity(Quantity));    //Validates user input of quantity
            MedicineDetail[*ptr][0]=Id;
            MedicineDetail[*ptr][1]=Quantity;
            strcpy(MedicineName[*ptr],Name);
            (*ptr)++;   //Increase the count of medicines
            printf("New medicine added successfully\n");
        }
    }
}
int SearchMedicine(int MedicineDetail[][2],int NoOfMedicine){
    int Id,found=-1;
    do{
        printf("Enter medicine Id \n");
        scanf("%d",&Id);
    }while(!ValidateId(Id));    //Validates user input of Id
    for(int a=0;a<NoOfMedicine;a++){
        if(MedicineDetail[a][0]==Id){
            found=a;    //Stores the index at which the medicine is found
            break;
        }
    }
    return found;
}
void ModifyMedicine(int MedicineDetail[][2],char MedicineName[][31],int NoOfMedicine){
    int option,Quantity;
    char Name[31];
    int index=SearchMedicine(MedicineDetail,NoOfMedicine);  //Uses search function to check if medicine exists or not
    if(index==-1)   
        printf("Medicine Id does not exist\n");
    else{    
        do{
            printf("If you want to change only medicine name,enter 1 or enter 2 for only changing quantity or enter 3 for both \n");
            scanf("%d",&option);
        }while(option<1||option>3);
        switch (option){
        case 3: //Uses concept of fall-through in switch cases for option 3
        case 1:
            do{
                printf("Enter the new medicine name.It cannot be more than 30 characters \n");
                scanf("%30s",Name);
            }while(!ValidateName(Name));
            strcpy(MedicineName[index],Name);
            printf("Medince name updated successfully\n");
            if(option==1)
                break;
        case 2:
            do{
                printf("Enter the new quantity of the medicine \n");
                scanf("%d",&Quantity);
            }while(!ValidateQuantity(Quantity));
            MedicineDetail[index][1]=Quantity;
            printf("Medince quantity updated successfully\n");
            break;
        }
    }
}
void DeleteMedicine(int MedicineDetail[][2],char MedicineName[][31],int *ptr){
    int index=SearchMedicine(MedicineDetail,*ptr);
    if(index==-1)
        printf("Medicine Id does not exist\n");
    else{
        for(int a=index;a<*ptr;a++){    //Deletes the record by shifting each record back by one index
            MedicineDetail[a][0]=MedicineDetail[a+1][0];
            MedicineDetail[a][1]=MedicineDetail[a+1][1];
            strcpy(MedicineName[a],MedicineName[a+1]);
        }
        (*ptr)--;   //Updates the value of number of medicines
        printf("Medicine record deleted successfully\n");
    }
}
void DisplayInventory(int  MedicineDetail[][2],char MedicineName[][31],int NoOfMedicine){
    printf("Id\tName\t\tQuantity\n");
    for(int a=0;a<NoOfMedicine;a++){
        printf("%d\t%s\t\t%d\n",MedicineDetail[a][0],MedicineName[a],MedicineDetail[a][1]);
    }
}
int main(){
    char MedicineName[size][31];
    int MedicineDetail[size][2],NoOfMedicine=0 ,userinput;
    printf("Welcome to Medicine Managment System!");
    do{
        printf("To:\nAdd a new medicine record,enter 1\nSearch for a medicine,enter 2\nModify an existing record,enter 3\nDelete a existing record,enter 4\nDisplay inventory\nExit the system,enter 6 \n");
        scanf("%d",&userinput);
        switch (userinput){
            case 1:
                AddMedicine(MedicineName,MedicineDetail,&NoOfMedicine);
                break;
            case 2:
                int result=SearchMedicine(MedicineDetail,NoOfMedicine);
                (result==-1)?printf("Medicine not found in inventory\n"):printf("Medicine found at index %d\n",result);
                break;
            case 3:
                ModifyMedicine(MedicineDetail,MedicineName,NoOfMedicine);
                break;
            case 4:
                DeleteMedicine(MedicineDetail,MedicineName,&NoOfMedicine);
                break;
            case 5:
                DisplayInventory(MedicineDetail,MedicineName,NoOfMedicine);
                break;
            case 6:
                printf("Exitted");
                break;
            default:
                printf("Invalid option\n");
        }
    }while(userinput!=6);
}