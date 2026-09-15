#include <stdio.h>

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
int totalBedCapacity[WARD_COUNT]={20,10,10,05};
int bedOccupancy[4][20] ={0};

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int emergencyLevel[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];
int admittedToWard[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];

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

int main()
{
    printf("==============================================================\n");
    printf("SMART HOSPITAL RESOURCE ALLOCATION SYSTEM\n");
    printf("==============================================================\n");
    printf("Doctor Specialties Data\n");
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
    printf("\nPatient Registration\n");
    printf("---------------------------\n");
    printf("Enter Patient name:");
    scanf("  %[^\n]", patientName[patientCount]);
    printf("Enter Patient age:");
    scanf("%d", &patientAge[patientCount]);
    printf("Enter emergency Level(1-Normal,2=urgent,3=critical):");
    scanf(" %d", &emergencyLevel[patientCount]);
    printf("Enter Specialty ID(1-4):");
    scanf("%d",&patientSpecialty[patientCount]);

    printf("Is Admitted Ward?(1=Yes,0=No):");
    scanf(" %d", &admittedToWard[patientCount]);
      if (admittedToWard[patientCount]==1){
        printf("Enter Ward ID(1-4):");
        scanf("%d",&patientWard[patientCount]);

        printf("Enter days of Admitted:");
        scanf("%d",&daysAdmitted[patientCount]);
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

    specialtyQueueCount[patientSpecialty[patientCount]-1]++;

    patientCount++;
    printf("\nPatient Registerd Succesfully.\n");


    return 0;
}
