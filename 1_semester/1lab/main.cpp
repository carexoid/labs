#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int partition (vector<int> &arr, int low, int high){
    int i = low;
    for (int j = low; j <= high - 1; j++){

        if (arr[j] < arr[high]){
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void quickSort(vector<int> &arr, int low, int high){
    if (low < high){

        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0, 2);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

int maxNum (vector<int> vec){
    int res=0;
    for (int i=0;i<vec.size();i++){
        if (vec[res]<vec[i])
            res = i;
    }
    return res;
}


void divider (int m,int numOfArr,FILE* input,int sizeOfInput){
    cout<<"ii";
    vector<int> division(numOfArr);
    //vector<FILE*> divided[numOfArr];
    FILE *divided[numOfArr];
    vector<int> cage;
    string ending = ".bin";
    int notNum = -1;

   // FILE* output;
    for (int i=0;i<numOfArr;i++){
        string name= to_string(i) + ending;
        const char* namec = name.c_str();
        divided[i] = fopen(namec, "w");
    }

   // int sizeOfInput = fsize ( input );
    int amountOfCages = sizeOfInput / m + 1;
    int sum = 1;
    division [0] = 1;
    while (amountOfCages > sum) {
        int maximalInd = maxNum(division);
        int maximal = division[maximalInd];

        for (int i = 0; i < division.size(); i++)
            division[i] += maximal;
        division[maximalInd] = 0;
        sum += (maximal * (division.size() - 2));
    }
    int numOfOversize = sizeOfInput % sum;
    int j = 0, k = 0;
    bool flag = 0;
    int mNew = sizeOfInput / sum;
    cage.resize(mNew+1);
    while (j < numOfOversize ){
        while (division[k] && !flag ){
            for (int l=0;l<mNew+1;l++){
                fread (&cage[l],sizeof(int),1,input);
            }

            quickSort(cage,0,mNew);
            //sort(cage.begin(),cage.end());
            for (int l=0;l<mNew+1;l++){
               fwrite ( &cage[l] , sizeof(int) , 1 , divided[k]);
            }

            fwrite (&notNum, sizeof(int) , 1, divided[k]);

            division[k]--;
            j++;
            if (j == numOfOversize)
                flag = 1;
        }
        if (flag)
            break;
        k++;
    }
    cage.resize(mNew);
    while (k < numOfArr){
        while (division[k]){
            for (int l=0;l<mNew;l++){
                fread (&cage[l],sizeof(int),1,input);
            }
            quickSort(cage,0,mNew-1);
            //sort(cage.begin(),cage.end());
            for (int l=0;l<mNew;l++){
                fwrite ( &cage[l] , sizeof(int) , 1 , divided[k]);
            }
            fwrite (&notNum, sizeof(int) , 1, divided[k]);

            division[k]--;
        }
        k++;

    }
    for (int i=0;i<numOfArr;i++){
        fclose(divided[i]);
    }

}

bool ready (vector<FILE*> divided){
    int counter = 0;
    for (int i = 0; i<divided.size(); i++)
        if (getc(divided[i]) != EOF)
            counter++;
    for (int i = 0; i<divided.size(); i++)
        fseek(divided[i],0,0);
    return counter == 1;
}

bool checker (vector<int> front , int curOut){
    int counter = 0;

    for (int i=0;i< front.size();i++){
        //cout<<front[i];
        //cin>>front[i];
        if (i!=curOut && front[i] >0)
            counter++;
    }
    if (!counter)
        return 1;
    return 0;
}

bool empt (FILE* f){
    fpos_t  p;
    fgetpos(f,&p);
    if (getc(f) == EOF){
        return 1;
    }
    fsetpos(f,&p);
    //if (feof(f))
       // return 1;
    return 0;
}
bool cont (vector<FILE*> divided,int k){
    for (int i =0;i<divided.size();i++)
        if (i!=k)
            if (empt(divided[i]))
                return 0;
    return 1;


}

void merger (int numOfArr){
    int notNum = -1;
    string ending = ".bin";
    vector<FILE*> divided(numOfArr);
    vector<int> front(numOfArr,0);
    FILE *helper,*res;
    for (int i=0;i<numOfArr;i++){
        string name= to_string(i) + ending;
        const char* namec = name.c_str();
        divided[i] = fopen(namec, "r+w");
    }

    while (!ready(divided)){
        int curOut = 0;
        for (int i = 0; i<divided.size(); i++){
            if (getc(divided[i]) == EOF)
                curOut = i;
            fseek(divided[i],0,0);
        }


        while (cont(divided,curOut)){
            for (int i = 0; i < numOfArr; i++){
                if(i!=curOut ){
                    fread( &front[i],sizeof(int),1,divided[i]);
                }
            }
            while (!checker(front,curOut)){
                int minimal = 10000000, minimalInd = 0;
                for (int i = 0; i<numOfArr; i++){
                    if (i!=curOut && front[i]!=-1 ){
                        if (front[i]<=minimal){
                            minimal=front[i];
                            minimalInd = i;
                           // cout <<front[i]<<endl;
                        }
                    }
                }
                fwrite (&minimal,sizeof(int),1,divided[curOut]);
                fread (&front[minimalInd],sizeof(int),1,divided[minimalInd]);
            }
            fwrite (&notNum,sizeof(int),1,divided[curOut]);
            /*for (int i =0;i<front.size();i++){
                if (i!=curOut)
                    fread (&front[i], sizeof(int),1 ,divided[i]);
            }*/
        }
        for (int i = 0; i<numOfArr;i++){
            if (i!= curOut){
                int numer;
                helper = fopen("helper.bin","w");
                while (!feof(divided[i])){
                    if (fread(&numer,sizeof(int),1,divided[i]))
                        fwrite(&numer,sizeof(int),1,helper);
                }
                fclose(divided[i]);
                fclose(helper);
                string name= to_string(i) + ending;
                const char* namec = name.c_str();
                divided[i] = fopen(namec, "w");
                helper = fopen("helper.bin","r");
                while (!feof(helper)){
                    if (fread(&numer,sizeof(int),1,helper))
                        fwrite(&numer,sizeof(int),1,divided[i]);
                }
                fclose(divided[i]);
                fclose(helper);

                divided[i] = fopen(namec, "r+w");

            }
        }
        fseek(divided[curOut],0,0);
        res = divided[curOut];


    }
    int numeric;
    FILE* result = fopen("output.bin","w");
    while (!feof(res)){
        if (fread(&numeric,sizeof(int),1,res))
            fwrite(&numeric,sizeof(int),1,result);
    }
    fclose(result);
    for (int i=0;i<numOfArr;i++){
        fclose(divided[i]);
    }


}

void generator (int sizeOfRand){
    int a;
    srand( time(0));
    FILE* inp = fopen("input.bin","w");
    for (int i = 0; i < sizeOfRand; i++){
        a = 1 + rand() % 100000;
        fwrite (&a, sizeof(int), 1, inp);
        cout << a <<" ";
    }
    fclose(inp);
}

void outp (FILE* f){
    int a;
    while(!feof(f)){
        fread(&a,sizeof(int),1,f);
        cout << a << " ";
    }
    cout << '\n';
    fclose(f);
}

int main() {
    FILE* creator;
    char com;
    int m,numOfArr,sizeOfRand;
    string ending = ".bin";
    cout<<"Enter size of memory: ";
    cin>>m;
    cout<<"\nEnter number of files: ";
    cin>>numOfArr;
    for (int i = 0; i < numOfArr ; i++){
        string name= to_string(i) + ending;
        const char* namec = name.c_str();
        creator = fopen(namec,"w");
        fclose(creator);
    }
    cout << "\nDo you want to generate new input? (y/n) :";
    cin >> com;
    if (com == 'y'){
        cout<<"\nNumber of elements in input: ";
        cin >> sizeOfRand;
        cout << "\n";
        /*   for (int i = 0; i < numOfArr ; i++){
               string name= to_string(i) + ending;
               const char* namec = name.c_str();
               outp(fopen(namec,"r"));
           }*/

        generator( sizeOfRand );

    }


    FILE* input = fopen("input.bin","r+w");

    divider(m, numOfArr, input, sizeOfRand);
    cout << "\nResult of divider:\n";
    for (int i = 0; i < numOfArr ; i++){
        string name= to_string(i) + ending;
        const char* namec = name.c_str();
        cout << i+1 << ": ";
        outp(fopen(namec,"r"));
    }
    cout<<"\nResult of merge: ";
    merger(numOfArr);
    fclose(input);
    outp(fopen("output.bin","r"));

    return 0;
}