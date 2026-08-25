#include <stdio.h>

#define SPECIALTY_COUNT 4
#define WARD_COUNT 4

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
    return 0;
}
