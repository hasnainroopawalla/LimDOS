#include<iostream>
#include<string>
#include <cstdlib>
#include<iomanip>
#include<math.h>
#include <unistd.h>
#include <windows.h>
#define COUNT 10
using namespace std;
char a[64];
int ccc,ll[10]={0},ptrcomp,superuser=0,flagdel=0,fsize,pp,len,flagcd=0,i,h=2,test=1,   filech,l,ch,tempstart,c,k=1,endd,last=0,ptrf=0,j,flag=0;
char opp,d,n;
string temppro,wrdata;
float avgwt,avgtt;
int ppp,opx,opy,templen,ptrfind,startf[10]={0};
int prott[50],proct[50],prowt[50],proat[50],proi,mather[50]={0},tempmather,tempprobt,probt[50],lenf[10]={0};
string proname[50],statustemp,prodataa,compstr,namecomp[10],datacomp[10],execstr,deltemp,pas,dele,data,name[10],fil,dir,chg,cur="",str="";
double proans[50],tempproans;

char trav[5]={'l','l','@'};
struct processnode
{
    string prodata;
    double ans;
    int prostatus;
    processnode *next;
}*prostart,*prolast,*proptr,*proptr1;

struct node
{
    string path;
    node *left,*right,*root;
    int isfile;
}*start,*ptr,*ptrls,*ptrtemp;

void createprocessnode(string prodataa)
{
    processnode *pronode=new processnode;
    pronode->prodata=prodataa;
    pronode->ans=0;
    pronode->prostatus=0;
    pronode->next=NULL;
    if(prostart==NULL)
    {
        prostart=pronode;
        prolast=pronode;
    }
    else
    {
        prolast->next=pronode;
        prolast=pronode;
    }
    cout<<"\nProcess Created.\n\n"<<endl;
}
void deletepro(string delpro)
{
    int proflag=0;
    proptr=prostart;
    proptr1=proptr->next;
    if(!proptr->prodata.compare(delpro))
    {
        prostart=prostart->next;
        proflag=1;
    }
    else
    {
        while(proptr1->next!=NULL)
        {
            if(!proptr1->prodata.compare(delpro))
            {
                    proflag=1;
                proptr->next=proptr1->next;
            }
            else
                proflag=0;
                proptr1=proptr1->next;
                proptr=proptr->next;
        }
        if(!proptr1->prodata.compare(delpro))
        {
            proptr->next=NULL;
            prolast=proptr;
            proflag=1;
        }
    }
    if(proflag==1)
        cout<<"\nProcess Deleted.\n\n"<<endl;
    else
        cout<<"\nProcess not found.\n\n"<<endl;



}
void disppro()
{
    cout<<"\n";

    proptr=prostart;
    if(proptr==NULL || prostart==NULL)
        cout<<"No Processes.\n\n"<<endl;
    else{
        if(proptr->prostatus==0)
            statustemp="Incomplete";
        else
            statustemp="Complete";
    cout<<"  Process\t Status\n";
    while(proptr->next!=NULL)
    {
        if(proptr->prostatus==0)
            statustemp="Incomplete";
        else
            statustemp="Complete";
        cout<<"    "<<proptr->prodata<<"\t\t"<<statustemp<<endl;
        proptr=proptr->next;
    }
        cout<<"    "<<proptr->prodata<<"\t\t"<<statustemp<<endl;
         cout<<"\n\n"<<endl;
    }
}
void print2DUtil(struct node *root, int space=0)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<"\n";
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->path;

    // Process left child
    print2DUtil(root->left, space);
}
void print2D(struct node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

void ls()
{
    print2D(ptr);
    cout<<"\n\n";
}

void disppath()
{
    cur="";
    i=0;
    ptr=start;
    cur=cur+ptr->path;
    while(trav[i]!='@')
    {
        if(trav[i]=='l')
        {
            ptr=ptr->left;
        }
        else
        {
            ptr=ptr->right;
        }
        cur=cur+"/"+ptr->path;
        i++;
    }
    cout<<cur;
}

void cdback()
{
    i--;
    trav[i]='@';
    h--;
    if(h<0)
        h=0;
}

void cdd(string mchg)
{
    flagcd=0;
    if(ptr->left!=NULL)
    {
        ptr=ptr->left;
        if(!ptr->path.compare(mchg))
        {
            flagcd=1;
            h++;
            trav[i]='l';
            i++;
            trav[i]='@';
        }
        else
        {
            ptr=ptr->root;
        }
    }
    if(ptr->right!=NULL)
    {
        ptr=ptr->right;
        if(!ptr->path.compare(mchg))
        {
            flagcd=1;
            h++;
            trav[i]='r';
            i++;
            trav[i]='@';
            //ptr=ptr->right;
        }
        else
        {
            ptr=ptr->root;
        }
    }
    if(flagcd==0)  //flagcd=0 is not found
    {
            cout<<"Directory not found.\n\n"<<endl;
    }

}

void mkdir(string dir)
{
    if(ptr->left!=NULL && ptr->right!=NULL)
    {
        cout<<"No space to create directory.\n\n"<<endl;
    }
    else if(ptr->isfile==1)
    {
        cout<<"Cannot create directory here.\n\n"<<endl;
    }
    else if(ptr->left==NULL)
    {
        node *newnode=new node;
        newnode->right=NULL;
        newnode->left=NULL;
        newnode->isfile=0;
        ptr->left=newnode;
        newnode->root=ptr;
        newnode->path=dir;
        cout<<dir<<" created.\n\n"<<endl;
    }
    else if(ptr->right==NULL)
    {
        node *newnode=new node;
        newnode->right=NULL;
        newnode->left=NULL;
        newnode->isfile=0;
        ptr->right=newnode;
        newnode->root=ptr;
        newnode->path=dir;
        cout<<dir<<" created.\n\n"<<endl;

    }
}

void createfile(string n,int l,string dataf)
{
    c=0;
    flag=0;
    for(i=0;i<64;i++)
    {

        if(a[i]=='0')
        {
            c++;
        }
        else
        {
            c=0;
        }
        if(c==l)
        {
            tempstart=i-l+1;
            flag=1;
            break;
        }
    }
    if(flag==1)    //insert
    {
        filech=0;
        endd=(tempstart+l)-1;
        for(i=tempstart;i<=endd;i++)
        {
            a[i]=dataf.at(filech);
            filech++;
        }
        ptrf=0;
        while(lenf[ptrf]!=0)
        {
            ptrf++;
        }
        lenf[ptrf]=l;
        name[ptrf]=n;
        startf[ptrf]=tempstart;
        cout<<"\n"<<n<<" created.\n\n"<<endl;
    }
    else
    {
        cout<<"Unallocatable File.\n\n"<<endl;
    }
    k++;
    ptrf++;
}

void mkfile(string fil)
{
    cout<<"Enter Data: ";
    getline(cin,data);
    fsize=data.length();
    if(ptr->left!=NULL && ptr->right!=NULL)
    {
        cout<<"No space to create file.\n\n"<<endl;
    }
    else if(ptr->isfile==1)
    {
        cout<<"Cannot create file here.\n\n"<<endl;
    }
    else if(ptr->left==NULL)
    {
        node *newnode=new node;
        newnode->right=NULL;
        newnode->left=NULL;
        newnode->isfile=1;
        ptr->left=newnode;
        newnode->root=ptr;
        newnode->path=fil;
        createfile(fil,fsize,data);
    }
    else if(ptr->right==NULL)
    {
        node *newnode=new node;
        newnode->right=NULL;
        newnode->left=NULL;
        newnode->isfile=1;
        ptr->right=newnode;
        newnode->root=ptr;
        newnode->path=fil;
        createfile(fil,fsize,data);
    }
}
void deletefile(string d)
{
    ptrf=0;
    flag=0;
    while(name[ptrf]!=d)
    {
        ptrf++;
        if(ptrf==10)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        cout<<endl<<"File not found in FAT Table.\n\n"<<endl;
    }
    else
    {
        for(i=startf[ptrf];i<startf[ptrf]+lenf[ptrf];i++)
        {
            a[i]='0';
        }
        cout<<endl<<name[ptrf]<<" Deleted.\n\n"<<endl;
        name[ptrf]="";
        startf[ptrf]=0;
        lenf[ptrf]=0;
    }
}
void del()
{
    if(ptr->left==NULL && ptr->right==NULL)
    {
            deltemp=ptr->path;

            if(ptr->isfile==1)
            {
                deletefile(deltemp);
                ptr=ptr->root;
                ptrtemp=ptr->left;

                if(!ptrtemp->path.compare(deltemp))
                {

                    ptr->left=NULL;
                }
                else
                {

                    ptrtemp=ptr->right;

                    if(!ptrtemp->path.compare(deltemp))
                    {

                        ptr->right=NULL;

                    }
                }
            }
            else
            {
                ptr=ptr->root;
                ptrtemp=ptr->left;

                if(!ptrtemp->path.compare(deltemp))
                {
                    ptr->left=NULL;
                }
                else
                {
                    ptrtemp=ptr->right;

                    if(!ptrtemp->path.compare(deltemp))
                    {

                        ptr->right=NULL;
                    }
                }
                cout<<"\n"<<deltemp<<" Deleted.\n\n"<<endl;

            }
            h--;
            trav[h]='@';

    }
        else
        {
            cout<<"Cannot delete as directory contains sub-directories.\n\n"<<endl;
        }
}

void startprogram()
{
    for(i=0;i<64;i++)
	{
		a[i]='0';
	}

    node *c=new node;
    c->path="C:";
    start=c;
    node *home=new node;
    home->path="Home";
    node *doc=new node;
    doc->path="Documents";
    node *desktop=new node;
    desktop->path="Desktop";
    node *hasnain=new node;
    hasnain->path="Hasnain";
    node *yash=new node;
    yash->path="Yash";

    c->root=NULL;
    c->left=home;
    c->right=doc;
        c->isfile=0;

    home->root=c;
    home->left=desktop;
    home->right=NULL;
        home->isfile=0;

    doc->root=c;
    doc->left=NULL;
    doc->right=NULL;
        doc->isfile=0;

    desktop->root=home;
    desktop->left=hasnain;
    desktop->right=yash;
        desktop->isfile=0;

    hasnain->root=desktop;
    hasnain->left=NULL;
    hasnain->right=NULL;
        hasnain->isfile=0;

    yash->root=desktop;
    yash->left=NULL;
    yash->right=NULL;
        yash->isfile=0;


        for(int z=0;z<50;z++)
            proat[z]=z+1;
}

void showmanual()
{
    cout<<"cd.. - "<<"\n\tGo to previous directory.\n"<<endl
        <<"cd 'directory name' - "<<"\n\tChange current directory.\n"<<endl
        <<"ls - "<<"\n\tList entire tree of sub-directories.\n"<<endl
        <<"mkdir 'directory name' - "<<"\n\tMake new folder in that directory.\n"<<endl
        <<"mkfile 'file name' - "<<"\n\tMake new file in that directory.\n"<<endl
        <<"read - "<<"\n\tRead a File.\n"<<endl
        <<"edit - "<<"\n\tEdit a File.\n"<<endl
        <<"dispmem - "<<"\n\tDisplay Memory.\n"<<endl
        <<"dispfat - "<<"\n\tDisplay FAT table.\n"<<endl
        <<"compact - "<<"\n\tPerform Compaction for Efficient memory storage.\n"<<endl
        <<"delete 'directory/file name' - "<<"\n\tDelete a directory/file.\n"<<endl
        <<"mkpro 'process data'- "<<"\n\tCreate a Process.\n"<<endl
        <<"showpro - "<<"\n\tDisplay all Processes.\n"<<endl
        <<"delpro - "<<"\n\tDelete a Process.\n"<<endl
        <<"execpro - "<<"\n\tExecute the batch of Processes.\n"<<endl
        <<"admin - "<<"\n\tSwitch to Admin mode.\n"<<endl
        <<"logout - "<<"\n\tLogout.\n"<<endl
        <<"ipconfig - "<<"\n\tDisplay Network details.\n"<<endl
        <<"clr - "<<"\n\tClear the screen.\n"<<endl
        <<"manual - "<<"\n\tDisplay all available commands.\n"<<endl
        <<"exit - "<<"\n\tQuit LimDOS.\n"<<endl<<endl<<endl;
}
void writefile()
{
    ccc=0;
    cout<<"Enter new data: ";
    getline(cin,wrdata);
    cout<<"\n";
    ptrfind=0;
    execstr="";
    while(ptr->path.compare(name[ptrfind]))
    {
        ptrfind++;
    }
    templen=lenf[ptrfind];
    if(wrdata.length()<=lenf[ptrfind])
    {
        for(int v=startf[ptrfind];v<wrdata.length()+startf[ptrfind];v++)
        {
            a[v]=wrdata.at(ccc);
            ccc++;
        }
        for(int v=startf[ptrfind]+wrdata.length();v<startf[ptrfind]+lenf[ptrfind];v++)
            a[v]='0';
        lenf[ptrfind]=wrdata.length();
        cout<<"Modifying File..\n"<<endl;
        Sleep(2000);
        cout<<"File Modified.\n\n"<<endl;
    }
    else
    {
        Sleep(800);
        cout<<"Data too large.\nData can be at most "<<templen<<" bits for this File.\n\n"<<endl;
    }
}
void readfile()
{
    ptrfind=0;
    execstr="";
    while(ptr->path.compare(name[ptrfind]))
    {
        ptrfind++;
    }
    for(int v=startf[ptrfind];v<lenf[ptrfind]+startf[ptrfind];v++)
    {
        execstr=execstr+a[v];
    }
    cout<<"Reading File..\n"<<endl;
    Sleep(2000);
    cout<<">"<<execstr<<endl<<endl<<endl;
}
void adjust()
{
    if(ptr->left==NULL && ptr->right!=NULL)
    {
        ptr->left=ptr->right;
        ptr->right=NULL;
    }
}


void compat()
{
    ptrcomp=0;
    for(int b=0;b<10;b++)
    {
        namecomp[b]="";
        datacomp[b]="";
        ll[b]=0;
    }
    while(ptrcomp!=10)
    {
        compstr="";
        if(lenf[ptrcomp]==0){
            }
        else
        {

            namecomp[ptrcomp]=name[ptrcomp];
            for(int b=startf[ptrcomp];b<lenf[ptrcomp]+startf[ptrcomp];b++)
            {
                compstr=compstr+a[b];
            }
            datacomp[ptrcomp]=compstr;
            ll[ptrcomp]=compstr.length();
        }

            ptrcomp++;
    }
     for(i=0;i<10;i++)
    {
        name[i]="";
        lenf[i]=0;
        startf[i]=0;
    }
    for(i=0;i<64;i++)
    {
        a[i]='0';
    }
    ptrcomp=0;
    while(ptrcomp!=10)
    {
        if(ll[ptrcomp]!=0)
        {
            createfile(namecomp[ptrcomp],ll[ptrcomp],datacomp[ptrcomp]);
        }
        ptrcomp++;
    }
    cout<<"Executing Compactation.."<<endl;
    Sleep(3000);
    cout<<"Complete."<<endl<<endl<<endl;
}

void dispcompletepro()
{
    avgtt=0.0;
    avgwt=0.0;
    cout<<"  Process     Answer\t\t Status\t\tBT\tCT\tTT\tWT\n";
    for(int z=0;z<=proi;z++)
    {
        if(mather[z]==1)
            statustemp="Incomplete";
        else
            statustemp="Complete";
        cout<<"    "<<proname[z]<<"\t\t"<<proans[z]<<"\t\t"<<statustemp<<"\t"<<probt[z]<<"\t"<<proct[z]<<"\t"<<prott[z]<<"\t"<<prowt[z]<<endl;
        avgtt=avgtt+prott[z];
        avgwt=avgwt+prowt[z];
    }
    proi++;
    avgtt=avgtt/proi;
    avgwt=avgwt/proi;
        cout<<"\n  Average Turn around Time= "<<avgtt<<"\n  Average Wait Time= "<<avgwt<<"\n\n"<<endl;
}

void execpro()
{
    if(prostart==NULL)
        cout<<"No Processes.\n\n"<<endl;
    else{

    proi=0;
    prowt[0]=0;
    proat[0]=1;
    proptr=prostart;
    while(proptr->next!=NULL)
    {
        mather[proi]=0;
        proname[proi]=proptr->prodata;
        opx=(int)proptr->prodata.at(0)-48;
        opy=(int)proptr->prodata.at(2)-48;
        opp=proptr->prodata.at(1);
        if(opp=='/'){
            probt[proi]=4;
            if(opy==0){
                 mather[proi]=1;
                 proans[proi]=99;}
                 else{
            proptr->ans=opx/opy;

            proans[proi]=(double)opx/(double)opy;
            proans[proi]=roundf(proans[proi]*100)/100;
            }}
        else if(opp=='*'){
            proptr->ans=opx*opy;
            probt[proi]=3;
            proans[proi]=opx*opy;}
        else if(opp=='+'){
            proptr->ans=opx+opy;
            probt[proi]=2;
            proans[proi]=opx+opy;}
        else if(opp=='-'){
            proptr->ans=opx-opy;
            probt[proi]=1;
            proans[proi]=opx-opy;}
            proptr=proptr->next;
            proi++;
    }
        proname[proi]=proptr->prodata;
        opx=(int)proptr->prodata.at(0)-48;
        opy=(int)proptr->prodata.at(2)-48;

        opp=proptr->prodata.at(1);
        if(opp=='/'){
                probt[proi]=4;
            if(opy==0){
                 mather[proi]=1;proans[proi]=99;}
                 else{
            proptr->ans=opx/opy;

            proans[proi]=(double)opx/(double)opy;
            proans[proi]=roundf(proans[proi]*100)/100;
}}
        else if(opp=='*'){
            proptr->ans=opx*opy;
            probt[proi]=3;
            proans[proi]=opx*opy;}
        else if(opp=='+'){
            proptr->ans=opx+opy;
            probt[proi]=2;
            proans[proi]=opx+opy;}
        else if(opp=='-'){
            proptr->ans=opx-opy;
            probt[proi]=1;
            proans[proi]=opx-opy;}
            proptr=proptr->next;

    for(int z=0;z<=proi;z++)
    {
        for(int y=z+1;y<=proi;y++)
        {
            if(probt[y]<probt[z])
            {
                temppro=proname[y];
                proname[y]=proname[z];
                proname[z]=temppro;

                tempprobt=probt[y];
                probt[y]=probt[z];
                probt[z]=tempprobt;

                tempmather=mather[y];
                mather[y]=mather[z];
                mather[z]=tempmather;

                tempproans=proans[y];
                proans[y]=proans[z];
                proans[z]=tempproans;

            }
        }
    }
    proct[0]=proat[0]+probt[0];
    for(int z=1;z<=proi;z++)
    {
        proct[z]=proct[z-1]+probt[z];               //completion time
    }
    for(int z=0;z<=proi;z++)
    {
        prott[z]=proct[z]-proat[z];
        prowt[z]=prott[z]-probt[z];              //turnaround time
    }
    cout<<"\nExecuting Processes.."<<"\n\n";
    Sleep(0.25*((proi+1)*1000));
    dispcompletepro();
    prostart=NULL;
    }
}






int main()
{
    prostart=NULL;
    prolast=NULL;
    cout<<endl;
    cout<<"                                            WELCOME TO LimDOS v1.0!"<<endl<<"                                         use 'manual' to get started.";
    cout<<endl<<endl;
    startprogram();
    do{
        disppath();
        adjust();
        cout<<">";
        test++;
        getline(cin,str);
        cout<<"\n";

        if(!str.compare("cd.."))
        {
            cdback();
        }
        else if(!str.find("cd "))
        {
            chg="";
            len=str.length();
            for(pp=3;pp<len;pp++)
            {
                chg=chg+str.at(pp);
            }
            cdd(chg);
        }
        else if(!str.find("mkdir "))
        {
            dir="";
            len=str.length();
            for(pp=6;pp<len;pp++)
            {
                dir=dir+str.at(pp);
            }
            mkdir(dir);
        }
        else if(!str.find("mkfile "))
        {
            fil="";
            len=str.length();
            for(pp=7;pp<len;pp++)
            {
                fil=fil+str.at(pp);
            }
            mkfile(fil);
        }
        else if(!str.compare("delete"))
        {
            del();
        }
        else if(!str.compare("ls"))
        {
            ls();
        }
        else if(!str.compare("compact"))
        {
            if(superuser==1)
            {
                compat();
            }
            else
            {
                cout<<"Insufficient Privileges.\n\n"<<endl;
            }
        }
        else if(!str.compare("manual"))
        {
            showmanual();
        }
        else if(!str.compare("execpro"))
        {
            execpro();
        }
        else if(!str.compare("logout"))
        {
            if(superuser==1){
                superuser=0;
                cout<<"Logged out.\n\n"<<endl;}
            else
                cout<<"Not Logged in.\n\n"<<endl;
        }
        else if(!str.compare("admin"))
        {
            cout<<"\nEnter password: ";
            getline(cin,pas);
            if(!pas.compare("1234"))
            {
                superuser=1;
                cout<<"\nYou are now an Admin.\n\n"<<endl;
            }
            else
            {
                cout<<"\nIncorrect Password.\n\n"<<endl;
            }

        }
        else if(!str.compare("exit"))
        {
            cout<<"\nThank you for using LimDOS.\n\n"<<endl;
            Sleep(2000);
            exit(0);
        }
        else if(!str.compare("read"))
        {
            if(ptr->isfile==1)
                readfile();
            else
                cout<<"Not a File.\n\n"<<endl;
        }
         else if(!str.compare("edit"))
        {
            if(ptr->isfile==1)
                writefile();
            else
                cout<<"Not a File.\n\n"<<endl;
        }
        else if(!str.find("mkpro "))
        {
            prodataa="";
            len=str.length();
            if(len>9)
                cout<<"Invalid Process Length.\n\n"<<endl;
            else{
            if((int)str.at(6)-48>=0 && (int)str.at(6)-48<=9 && (int)str.at(8)-48>=0 && (int)str.at(8)-48<=9 &&
               (str.at(7)=='/' || str.at(7)=='+' || str.at(7)=='-' || str.at(7)=='*')){
            for(pp=6;pp<len;pp++)
            {
                prodataa=prodataa+str.at(pp);
            }

            createprocessnode(prodataa);
            }
            else
                cout<<"Invalid Process Name.\n\n"<<endl;
            }
        }
        else if(!str.find("delpro "))
        {
            prodataa="";
            len=str.length();
            for(pp=7;pp<len;pp++)
            {
                prodataa=prodataa+str.at(pp);
            }
            deletepro(prodataa);
        }
        else if(!str.compare("showpro"))
        {
             disppro();
        }
        else if(!str.compare("clr"))
        {
            system ("CLS");
            cout<<"\n";
        }
        else if(!str.compare("ipconfig"))
        {
             system("C:\\Windows\\System32\\ipconfig");
             cout<<"\n"<<endl;
        }
        else if(!str.compare("dispmem"))
        {
            if(superuser==1)
            {
                int memi=0;
                cout<<"\n";
                for(i=1;i<=64;i++)
                {
                    cout<<a[memi]<<" ";
                    memi++;
                    if(i%16==0 && i!=0){
                    cout<<endl;}
                }
                cout<<"\n\n\n";
            }
            else
                {
                cout<<"Insufficient Privileges.\nUse 'admin' command.\n"<<endl;
            }

        }
        else if(!str.compare("dispfat"))
        {
             if(superuser==1)
            {
            cout<<"\n";
            cout<<"File\t\tStart\tLength"<<endl;
            for(i=0;i<10;i++)
            {
                    cout<<"  "<<name[i]<<"\t\t  "<<startf[i]<<"\t  "<<lenf[i]<<endl;
            }
            cout<<"\n\n";
         }
            else
            {
            cout<<"Insufficient Privileges.\nUse 'admin' command.\n"<<endl;
            }
        }
        else        //Not valid
        {
            cout<<"Invalid Command\nUse 'manual' for help.\n"<<endl;
        }
    }while(str.compare("exit"));
}
