#include <stdio.h>
#include<string.h>

#define SPECIALTY_COUNT 4
#define WARD_COUNT 4
#define MAX_PATIENTS 100

/*Doctor specialties data*/
int specialtyID[SPECIALTY_COUNT] ={1,2,3,4};
char specialtyName[SPECIALTY_COUNT][30] = {"General Practice(OPD)","Paediatrics","Cardiology","Neurology"};
float consultationFee[SPECIALTY_COUNT]={1500.00,2500.00,4500.00,5000.00};
int consultationTime[SPECIALTY_COUNT]={15,20,30,30};
int dailyPatientCap[SPECIALTY_COUNT]={30,20,12,10};

int wardID[WARD_COUNT]={1,2,3,4};
char wardName[WARD_COUNT][30]={"General Ward","Paediatric Ward","Surgical Ward","ICU(Intensive Care Unit)"};
float dailyBedRate[WARD_COUNT]={3000.00,6000.00,12000.00,25000.00};
int totalBedCapacity[WARD_COUNT]={20,10,10,5};
int bedOccupancy[4][20] ={0};

char patientID[MAX_PATIENTS][20];
char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int emergencyLevel[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int admittedToWard[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];

float patientFinalAmount[MAX_PATIENTS];
float patientDiscount[MAX_PATIENTS];
int specialtyQueueCount[SPECIALTY_COUNT]= {0};

int patientCount=0;
float calculateWaitingTime(int queueCount, int consulationTime)
{
    return queueCount * consulationTime;
}

float calculateSurcharge(float consulationFee, int emergencyLevel)
{
    if (emergencyLevel==1)
    {
        return 0;
    }else if(emergencyLevel==2)
    {
        return consulationFee * 0.20;
    }
    else if (emergencyLevel==3)
    {
        return consulationFee * 0.50;
    }else
    {
     return 0;
    }
}
float calculateWardCost(int wardID,int days)
    {
        if (wardID >= 1 && wardID <= WARD_COUNT)
        {
            return dailyBedRate[wardID -1] * days;
        }else
        {
            return 0;
        }
    }
float calculateAgeSubsidy(int age,float grossAmount)
{
    if (age <5 || age >65)
    {
        return grossAmount * 0.15;
    }else
    {
        return 0;
    }
}
void sortPatientsByPriority()
{  for(int i=0;i<patientCount-1;i++)
    { for (int j=i+1;j<patientCount;j++)
    {
        if(emergencyLevel[i]< emergencyLevel[j])
     {  int temp;
        temp= emergencyLevel[i];
        emergencyLevel[i]=emergencyLevel[j];
        emergencyLevel[j]=temp;

        int tempAge;
        tempAge=patientAge[i];
        patientAge[i]=patientAge[j];
        patientAge[j]=tempAge;

        char tempID[20];

        strcpy(tempID,patientID[i]);
        strcpy(patientID[i],patientID[j]);
        strcpy(patientID[j],tempID);

        char tempName[50];

        strcpy(tempName,patientName[i]);
        strcpy(patientName[i],patientName[j]);
        strcpy(patientName[j],tempName);

        int tempSpecialty;

        tempSpecialty=patientSpecialty[i];
        patientSpecialty[i]=patientSpecialty[j];
        patientSpecialty[j]=tempSpecialty;

        int tempWard;
        tempWard=patientWard[i];
        patientWard[i]=patientWard[j];
        patientWard[j]=tempWard;

        int tempAdmitted;

        tempAdmitted=admittedToWard[i];
        admittedToWard[i]=admittedToWard[j];
        admittedToWard[j]=tempAdmitted;

        int tempDays;
        tempDays=daysAdmitted[i];
        daysAdmitted[i]=daysAdmitted[j];
        daysAdmitted[j]=tempDays;

         float tempAmount;
         tempAmount=patientFinalAmount[i];
         patientFinalAmount[i]=patientFinalAmount[j];
         patientFinalAmount[j]=tempAmount;

         float tempDiscount;
         tempDiscount=patientDiscount[i];
         patientDiscount[i]=patientDiscount[j];
         patientDiscount[j]=tempDiscount;
}
 }
    }
     }
float calculateOccupancyPercentage(int ward)
{
    int occupiedBeds=0;
    for (int bed=0; bed<totalBedCapacity[ward];bed++){
        if (bedOccupancy[ward][bed]==1)
            {
            occupiedBeds++;
            }

            }return (occupiedBeds* 100.0)/totalBedCapacity[ward];
}
void saveBedStatus()
{
    FILE *file= fopen("beds_status.txt","w");
    if (file == NULL)
    {
        printf("Error opening beds_status.txt\n");
        return;
    }
    for ( int ward =0;ward<WARD_COUNT; ward++)
    {
        for(int bed=0;bed<totalBedCapacity[ward];bed++)
        {
            fprintf(file, "%d ",bedOccupancy[ward][bed]);
        }
    fprintf(file, "\n");
    }
    fclose(file);
    printf("\nBed Status Saved successfully\n");


}
void loadBedStatus()
{
    FILE *file;
    file = fopen("beds_status.txt","r");
    if (file == NULL)
    {
       return;
    }
    for ( int ward =0;ward<WARD_COUNT; ward++)
    {
        for(int bed=0;bed<totalBedCapacity[ward];bed++)
        {
            fscanf(file,"%d",&bedOccupancy[ward][bed]);
        }
    }
    fclose(file);

}
void savePatientRecord(int index)
{
    FILE *file= fopen("patient_records.txt","a");
    if (file == NULL)
    {
        printf("Error opening patient_records.txt\n");
        return;
    }
    fprintf(file, "Patient ID: %s\n",patientID[index]);
    fprintf(file, "Patient Name: %s\n",patientName[index]);
    fprintf(file, "Age: %d\n",patientAge[index]);
    fprintf(file, "Emergency Level: %d\n",emergencyLevel[index]);
    fprintf(file, "Final Amount: LKR %.2f\n",patientFinalAmount[index]);
    fprintf(file, "Discount: LKR %.2f\n",patientDiscount[index]);
    fprintf(file, "----------------------------------------------------\n");

    fclose(file);
    printf("Patient Record Saved Successfully.\n");
}
int main()
{
    loadBedStatus();
    printf("==============================================================\n");
    printf("SMART HOSPITAL RESOURCE ALLOCATION SYSTEM\n");
    printf("==============================================================\n");
    printf("Doctor Specialities Data\n");
    printf("-----------------------\n");

    for(int i=0; i<SPECIALTY_COUNT; i++)
    {
     printf("%d. %s - LKR %.2f - %d min - Cap: %d patients\n",specialtyID[i],specialtyName[i],consultationFee[i],consultationTime[i],dailyPatientCap[i]);

    }
    printf("\nHospital Wards Data\n");
    printf("---------------------\n");
    for (int i=0; i<WARD_COUNT; i++)
    {
        printf("%d. %s - LKR %.2f/day - capacity: %d beds\n",wardID[i],wardName[i],dailyBedRate[i],totalBedCapacity[i]);

    }
    printf("\nBed Availability\n");
    printf("-------------------\n");
    for (int ward =0 ; ward < WARD_COUNT; ward++)
    {
        printf("\n%s:\n",wardName[ward]);
           for(int bed=0; bed < totalBedCapacity[ward]; bed++)
           {
               if (bedOccupancy[ward][bed] == 0)

               {
                   printf("Bed %02d - Available\n", bed + 1);
               }
               else
               {
                   printf("Bed %02d- Occupied\n", bed + 1);
               }
           }
    }
    int anotherPatient=1;
    do
    {
    printf("\nPatient Registration\n");
    printf("---------------------------\n");
    printf("Enter Patient ID(e.g.,PAT-1001):");
    scanf(" %19[^\n]",patientID[patientCount]);
    printf("Patient ID:%s\n",patientID[patientCount]);
    printf("Enter Patient name:");
    scanf("  %[^\n]", patientName[patientCount]);
    printf("Enter Patient age:");
    scanf("%d", &patientAge[patientCount]);
    while(patientAge[patientCount]<0)
    {
        printf("Invalid age,Please enter valid age:");
        scanf("%d",&patientAge[patientCount]);
    }
    printf("Enter emergency Level(1-Normal,2=urgent,3=critical):");
    scanf(" %d", &emergencyLevel[patientCount]);
    while(emergencyLevel[patientCount]<1 || emergencyLevel[patientCount]>3)
     {
         printf("Invalid emergency level,please enter 1-3:");
         scanf("%d",&emergencyLevel[patientCount]);
     }
    printf("Enter Specialty ID(1-4):");
    scanf("%d",&patientSpecialty[patientCount]);
    while(patientSpecialty[patientCount] < 1 || patientSpecialty[patientCount]>4)
   {
       printf("Invalid specialty ID,Please Enter 1-4:");
       scanf("%d",&patientSpecialty[patientCount]);
   }
   if (specialtyQueueCount[patientSpecialty[patientCount]-1] >= dailyPatientCap[patientSpecialty[patientCount]-1])
   {
       printf("This Specialty has reached its daily patient capacity.\n");
       continue;
   }
    printf("Is Admitted Ward?(1=Yes,0=No):");
    scanf(" %d", &admittedToWard[patientCount]);
    while (admittedToWard[patientCount]!=0 && admittedToWard[patientCount]!=1)
    {
        printf("Invalid choice,please enter 1 for yes or 0 for no:");
        scanf("%d",&admittedToWard[patientCount]);
    }
      if (admittedToWard[patientCount]==1){
        printf("Enter Ward ID(1-4):");
        scanf("%d",&patientWard[patientCount]);
        while(patientWard[patientCount]<1 || patientWard[patientCount]>4)
        {
          printf("Invalid Ward ID,Please Enter 1-4:");
          scanf("%d",&patientWard[patientCount]);
        }
        printf("Enter days of Admitted:");
        scanf("%d",&daysAdmitted[patientCount]);
        while(daysAdmitted[patientCount]<=0)

        {
            printf("Invalid number of days,Please enter at least 1 day:");
            scanf("%d",&daysAdmitted[patientCount]);
        }

     int wardIndex=patientWard[patientCount]-1;
     int bedAllocated=0;
     for (int bed=0;bed<totalBedCapacity[wardIndex];bed++)
     {
         if (bedOccupancy[wardIndex][bed]==0)
            {
                bedOccupancy[wardIndex][bed]=  1;
                printf("Bed %d allocated succesfully.\n",bed+1);
                bedAllocated=1;
                break;
            }
         }
    if(bedAllocated==0)
    {
        printf("No available Beds in this ward.\n");
        patientWard[patientCount]=0;
        daysAdmitted[patientCount]=0;
        admittedToWard[patientCount]=0;
    }
    }
      else
      {
         patientWard[patientCount]=0;
         daysAdmitted[patientCount]=0;
      }

    float waitingTime;

    waitingTime=calculateWaitingTime(specialtyQueueCount[patientSpecialty[patientCount]-1], consultationTime[patientSpecialty[patientCount]-1]);
    printf("Estimated waiting Time:%.2f minutes\n",waitingTime);

    float surcharge;
    surcharge= calculateSurcharge(consultationFee[patientSpecialty[patientCount]-1],emergencyLevel[patientCount]);

    printf("Emergency Surcharge:LKR%.2f\n",surcharge);

    float wardCost;
    wardCost= calculateWardCost(patientWard[patientCount],daysAdmitted[patientCount]);

    printf("Ward cost: LKR %.2f\n",wardCost);

    float grossAmount = consultationFee[patientSpecialty[patientCount]-1]+surcharge+wardCost;
    printf("Gross Amount: LKR %.2f\n",grossAmount);

    float discount;
    discount=calculateAgeSubsidy(patientAge[patientCount],grossAmount);
    printf("Age subsidy: LKR %.2f\n",discount);
    patientDiscount[patientCount]=discount;

    float  finalAmount;
    finalAmount=grossAmount-discount;
    printf("Final Amount:%.2f\n",finalAmount);

    patientFinalAmount[patientCount]=finalAmount;

    specialtyQueueCount[patientSpecialty[patientCount]-1]++;

    patientCount++;

    savePatientRecord(patientCount - 1);

    sortPatientsByPriority();
    printf("\nDo you want to register another patient?(1=Yes, 0=No):");
    scanf("%d", &anotherPatient);
    }while(anotherPatient==1 && patientCount<MAX_PATIENTS);

    printf("\nPatient Registered Successfully.\n");
    printf("\nPatient Priority Order\n");
    printf("-------------------------\n");
    for(int i=0; i<patientCount;i++)
    {
        printf("%d. %s -Emergency Level: %d\n",i+1,patientID[i],patientName[i],emergencyLevel[i]);
    }
     printf("\nWard Occupancy Report\n");
     printf("-------------------------\n");
     for( int ward =0;ward < WARD_COUNT;ward++){
        int occupiedBeds=0;
      for (int bed=0; bed < totalBedCapacity[ward]; bed++){
        if (bedOccupancy[ward][bed]==1)
            {
            occupiedBeds++;
            }
     }
     int availableBeds=totalBedCapacity[ward]-occupiedBeds;
     printf("%s: Total= %d,occupied= %d, Available= %d, Occupancy=%.2f%%\n",wardName[ward],totalBedCapacity[ward],occupiedBeds,availableBeds,calculateOccupancyPercentage(ward));

     }
     printf("\nRevenue Report\n");
     printf("-------------------------\n");
     float totalRevenue=0;
     float totalDiscount=0;
     for (int i=0;i<patientCount;i++)
     {
         totalRevenue=totalRevenue+patientFinalAmount[i];
         totalDiscount=totalDiscount+patientDiscount[i];
     }
     int normalCount=0;
     int urgentCount=0;
     int criticalCount=0;

     for (int i=0;i<patientCount;i++)
     {
         if (emergencyLevel[i]==1)
         {
             normalCount++;
         }else if(emergencyLevel[i]==2)
         {
             urgentCount++;
         }else if(emergencyLevel[i]==3)
         {
             criticalCount++;
         }
     }
     printf("Total Patients: %d\n",patientCount);
     printf("Normal Patients:%d\n",normalCount);
     printf("Urgent Patients:%d\n",urgentCount);
     printf("Critical Patients:%d\n",criticalCount);

     printf("Total Revenue:LKR %.2f\n",totalRevenue);
     printf("Total Discounts:LKR %.2f\n",totalDiscount);
     int highestPatient=0;
     for(int i=1;i<patientCount;i++)
     {
         if(patientFinalAmount[i]>patientFinalAmount[highestPatient])
          {
              highestPatient=i;
          }
    }
    if(patientCount>0)
    {
        printf("Highest-paying patient:%s\n",patientName[highestPatient]);
        printf("Highest Patient Bill:LKR %.2f\n",patientFinalAmount[highestPatient]);
    }
    saveBedStatus();

    return 0;
}
