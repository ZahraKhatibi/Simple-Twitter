#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
vector <string> INSERT(string str);
vector <string> SELECT(string str);
vector <string> DELETE (string str);
vector <string> UPDATE (string str);
bool typesho_check_kon(string nemone , string olgo );
vector <string> sharhe_sharhe_kon (string str, char a);
vector <string> kodom_khate(string ki_o_chi , string jadval);
string parantez_hajf_kon(string str);
int operator_peyda_kon(string str);
bool update_check_kon( string jadval ,string donbal_chi_im, vector<string>chizaye_jadid );
vector<string> database(string stri);

int main()
{
    string stri;
    // cout << "dastor chie? " ;
    // getline(cin,stri);
    stri = "~$ INSERT INTO users VALUES (16,zahra,zahrakhtb1,123,Tue/Aug/11/23:45:26/2020,0);";
    database(stri);
}


vector<string> database(string stri)
{
   vector<string> khali;
    if (stri.substr(0,2) == "~$")
    {
        if (stri.substr(3,11) == "INSERT INTO")
            INSERT(stri.substr(15,stri.size()-15));

        else if (stri.substr(3,11)=="SELECT FROM")
            khali=SELECT(stri.substr(15,stri.size()-15));

        else if (stri.substr(3,11)== "UPDATE FROM")
            UPDATE(stri.substr(15,stri.size()-15));

        else if(stri.substr(3,11)=="DELETE FROM")
            DELETE(stri.substr(15,stri.size()-15));

        else
        {
            cout << "ERROR: ebarat vared shode joz dastorat motabar nist." << endl ;
            return khali;
        }

    }
        else
        {
            cout << "ERROR: vorodi bayad ba <<~$>> shoro shavad. " << endl ;
            return khali;
        }
    for(int i=0;i<khali.size();i++){
        cout<<khali[i]<<endl;
    }
    return khali;
}


vector <string> INSERT(string str)
{
    int i = 0;
    string esm_jadval="" , value = "" , etelaat="" ;
    vector <string> khali;
    while (str[i] != ' ')
    {
        esm_jadval += str[i];
        i++ ;
    }
    i = i + 1;
    while(str[i] != ' ')
    {
        value += str[i];
        i++ ;
    }
    if (value != "VALUES")
    {
        cout << "ERROR: ebarat vared shode shamel <<VALUES>> nist. " << endl;
        return khali;
    }
    i = i + 1;
    if(str[i] != '(')
    {
        cout << "ERROR: ebarat vared shode shamel << ( >> nist." << endl;
        return khali ;
    }
    if (str[str.size()-2] != ')')
    {
        cout << "ERROR: ebarat vared shode shamel << ) >> nist." << endl;
        return khali;
    }
    if (str[str.size()-1] != ';')
    {
        cout << "ERROR: ebarat vared shode shamel << ; >> nist." << endl;
        return khali ;
    }
    i = i + 1;
    vector <string> ghesmat;
    ghesmat = sharhe_sharhe_kon(str.substr(i,str.size()-i-2), ',');
    ifstream schema("schema.txt");
    bool check_kon = false;
    while(!schema.eof())
    {
        getline(schema,str);
        if(str == esm_jadval)
        {
            check_kon = true ;
            break;
        }
    }

    if (!check_kon)
    {
        cout << "ERROR: flie schema shamel esm jadval nist. " << endl;
        return khali;
    }


    vector<string> bakhsh;
    ofstream makefile((esm_jadval+".txt").c_str(),ios::app);
    makefile.close();
    int q = 0 ;
    string yekta = "";
    getline(schema,str);
    while (str !="")
    {
        bakhsh = sharhe_sharhe_kon(str, ' ');
        if(q>=ghesmat.size())
        {
            cout<<"ERROR: mizan motagheir haye vared shode bish az had mojaz ast. " << endl;
            return khali;
        }
        if (bakhsh.size() == 2)
        {
            if(!typesho_check_kon(ghesmat[q],bakhsh[1]))
            {
                cout << "ERROR: type vorodi haye vared shode ba type file schema moghayerat darad. " << endl;
                return khali;
            }
        }

        if (bakhsh.size() == 3)
        {
            if(!typesho_check_kon(ghesmat[q],bakhsh[2]))
            {
                cout << "ERROR: type vorodi haye vared shode ba type file schema moghayerat darad. " << endl;
                return khali;
            }
        }
        if(bakhsh.size() == 3)
        {
            ifstream filemon((esm_jadval+".txt").c_str());
            while(!filemon.eof())
            {
                getline(filemon,yekta);
                vector <string> yektaii;
                if(yekta=="")
                    break;
                yektaii = sharhe_sharhe_kon(yekta,' ');

                if(yektaii [q] == ghesmat[q])
                {
                    cout << "ERROR: ebarat vared shode yekta nist" << endl;
                    return khali;
                }
            }
            filemon.close();
        }
        q++ ;
        getline(schema,str);
    }
    schema.close();
    if( q != ghesmat.size())
    {
        cout << "ERROR: mizan motagheir haye vared shode bish az had mojaz ast." << endl ;
        return khali;
    }
    ofstream file_aslimon(( esm_jadval + ".txt" ).c_str(), ios::app);
    for(int z = 0 ; z < ghesmat.size() ; z++ )
    {
        file_aslimon << ghesmat[z];
        if( z != ghesmat.size()- 1 )
            file_aslimon <<' ';
    }
    file_aslimon << endl ;
    file_aslimon.close() ;
    return khali;
}


vector<string> sharhe_sharhe_kon (string str, char a)
{
    vector <string> sharhe_shode;
    string sharhe ="";
    int k = 0;
    while (str.size()>k)
    {
        while (str[k] != a)
        {
            sharhe += str[k];
            k++;
            if (k==str.size())
                break;
        }
        sharhe_shode.push_back(sharhe);
        sharhe = "";
        k++;
    }
    return sharhe_shode;
}


bool typesho_check_kon(string nemone , string olgo )
{
    if(olgo =="BOOLEAN")
    {
        if( nemone =="true" || nemone =="false")
            return true;
        return false;
    }


    if( olgo =="TIMESTAMP")
    {
        return true;
    }

    if(olgo.size()>4 && olgo.substr(0,4)=="CHAR")
    {
        int charsize = 0;
        stringstream change(olgo.substr(5,olgo.size()-6));
        change >> charsize ;
        if(nemone.size() > charsize )
            return false;
        return true;
    }

    if (olgo == "INTEGER")
    {
        int size = 0 ;
        string adad = "0123456789" ;
        for(int i = 0 ; i < nemone.size() ; i++)
        {
            for (int j = 0 ; j < 10 ; j++)
            {
                if( nemone[i] == adad[j])
                    size += 1;
            }
        }
        if (size == nemone.size())
            return true;
        else
            return false;
    }

    if(olgo.size()>7 && olgo.substr(0,7)=="INTEGER")
    {
        stringstream change(olgo.substr(8,olgo.size()-9));
        int sizeint = 0 ;
        change >> sizeint;
        vector<string> size_int = sharhe_sharhe_kon ( nemone ,'-' ) ;
        int size_vector = size_int.size();
        if(size_vector > sizeint )
            return false;
        for(int i=0 ;  i < size_vector ; i++)
        {
            if(!typesho_check_kon (size_int[i],"INTEGER"))
            {
                return false;
            }
        }
        return true;
    }
}


vector <string> SELECT(string str)
{

    vector <string> chap_kon_baram ;
    vector <string> khali;
    int i = 0 ;
    string esm_jadval = "" , donbal_chi_im = "" ;
    char alamat ;
    if(str[str.size()-1] != ';' )
    {
        cout << "ERROR: ebarat vared shode shamel << ; >> nist." <<endl ;
        return khali;
    }
    while (str[i] != ';' && str[i] != ' ')
    {
        esm_jadval += str[i];
        i++ ;
    }

    ofstream myfile(( esm_jadval +".txt").c_str(),ios::app);
    myfile.close();
    if (str[i] == ';')
    {
        ifstream myfile((esm_jadval +".txt").c_str());
        while (!myfile.eof())
        {
            getline(myfile , str);
            chap_kon_baram.push_back(str);
        }
        myfile.close();
        return chap_kon_baram ;
    }
    if (str[i] == ' ')
    {
        if ( str.substr(i+1,5) != "WHERE")
        {
                cout << "ERROR: ebarat vared shode shamel << WHERE >> nist." ;
                return khali;
        }
    }
    i = i + 7;
    str = str.substr(i,str.size()-i-1);
    return kodom_khate(str , esm_jadval) ;
}


vector<string> kodom_khate(string str , string jadval)
{
    vector <string> dige_vaghean_chap_kon_baram ;
    vector <string> natije1;
    vector <string> natije2;
    vector <string> natije3;
    string donbal_chi_im , jadval_peyda_kon="" , chio_peyda_konam = "";
    int i = 0 , koja = 0 , op_kojas = 0;
    char alamat ;
    str = parantez_hajf_kon(str) ;
    op_kojas = operator_peyda_kon(str);
    if(op_kojas == -1 )
    {
        while (str[i] != '!' && str[i] != '=')
        {
            donbal_chi_im += str[i] ;
                i++ ;
        }
        ifstream schema("schema.txt");
        while(!schema.eof()){
            getline(schema,jadval_peyda_kon);
            if(jadval_peyda_kon == jadval)
            {
                getline(schema,jadval_peyda_kon);
                while(jadval_peyda_kon!="")
                {
                    if( donbal_chi_im == sharhe_sharhe_kon(jadval_peyda_kon,' ')[0])
                        break;
                    getline(schema,jadval_peyda_kon);
                    koja++;
                }
            }
        }
        schema.close();

        alamat = str[i];
        i = i + 2 ;
        while (i<str.size())
        {
            chio_peyda_konam += str[i] ;
            i++ ;
        }

        ifstream myfile((jadval +".txt").c_str());
        string begir = "" ;
        if(alamat == '!')
        {
            while(!myfile.eof())
            {
                getline(myfile , begir);
                if (begir != "")
                {
                    if (sharhe_sharhe_kon(begir,' ')[koja] != chio_peyda_konam )
                        dige_vaghean_chap_kon_baram.push_back(begir);
                }
            }
        }
        if(alamat == '=')
        {
            while(!myfile.eof())
                {
                    getline(myfile , begir);
                    if (begir != "")
                    {
                        if(sharhe_sharhe_kon(begir,' ')[koja] == chio_peyda_konam)
                            dige_vaghean_chap_kon_baram.push_back(begir);
                    }
                }
        }
            myfile.close();
        return dige_vaghean_chap_kon_baram;
    }

    if (str[op_kojas] == 'O')
    {
        int temp = 1;
        natije1 = kodom_khate(str.substr(0,op_kojas),jadval);
        natije2 = kodom_khate(str.substr(op_kojas+2,str.size()-2-op_kojas),jadval);

        for(int a=0 ; a<natije1.size() ; a++)
        {
            for(int b=0 ; b < natije2.size() ; b++)
            {
                if(natije1[a] == natije2[b])
                    temp -= 1;
            }
            if(temp == 1)
            {
                natije2.push_back(natije1[a]);
            }
            temp = 1;
        }
        return natije2;
    }

    if (str[op_kojas] == 'A')
    {
        int temp = 1;
        natije1 = kodom_khate(str.substr(0,op_kojas),jadval);
        natije2 = kodom_khate(str.substr(op_kojas+3,str.size()-3-op_kojas),jadval);

        for(int a=0 ; a<natije1.size() ; a++)
        {
            for(int b=0 ; b < natije2.size() ; b++)
            {
                if(natije1[a] == natije2[b])
                    temp = 0;
            }
            if(temp == 0)
            {
                natije3.push_back(natije1[a]);
                temp = 1;
            }

        }
        return natije3;
    }
}


string parantez_hajf_kon(string str)
{
    int temp = 0 ;
    if (str[0]!= '(')
        return str;
    for(int i = 0 ; i < str.size() ; i++)
    {
        if (str[i] == '(')
            temp += 1;
        if (str[i]== ')')
            temp -= 1;
        if (temp == 0 && i<str.size()-2)
            return str;
    }
    str = str.substr(1,str.size()-2);
    return parantez_hajf_kon(str);
}


int operator_peyda_kon(string str)
{
    int shomare = 0 ;
    int temp = 0;
    for (int i = 0 ; i < str.size() ; i++)
    {
        if (str[i]=='(')
            temp += 1;
        if (str[i] == ')')
            temp -= 1;
        if((str[i]=='O' && temp == 0 ) || (str[i]=='A' && temp == 0 ))
        {
            shomare = i;
            break;
        }
    }
    if(shomare == 0)
        return -1 ;
    else
        return shomare;

}


vector <string> DELETE (string str)
{
    vector <string> chio_hazf_konam ;
    vector <string> kol_file ;
    vector <string> khali;
    string esm_jadval = "";
    int i=0 , temp = 1;
    while(str[i] !=' ' && str[i] != ';')
    {
        esm_jadval += str[i];
        i++;
    }
    if (str[i] == ';')
    {
        ofstream myfile1((esm_jadval +".txt").c_str());
        myfile1.close();
        return khali ;
    }
    i = i + 1;
    if (str.substr(i,5) != "WHERE" )
    {
        cout << "ERROR: ebarat vared shode shamel << WHERE >> nist.";
        return khali;
    }

    if (str[str.size()-1] != ';')
    {
        cout << "ERROR: ebarat vared shode shamel << ; >> nist.";
        return khali;
    }
    i = i + 6 ;
    str = str.substr(i,str.size()-i-1);
    chio_hazf_konam = kodom_khate(str,esm_jadval);
    ifstream myfile((esm_jadval +".txt").c_str());
    getline(myfile,str);
    while(!myfile.eof())
    {
        for(int a=0 ; a < chio_hazf_konam.size() ; a++)
        {
            if(chio_hazf_konam[a]==str)
                temp -= 1;
        }
        if (temp == 1)
        {
            kol_file.push_back(str);
        }
        getline(myfile,str);
        temp = 1;
    }
    myfile.close();
    ofstream myfile2((esm_jadval +".txt").c_str());
    for(int a=0 ; a<kol_file.size() ; a++)
        myfile2 << kol_file[a] << endl;
    myfile2.close();
    return khali ;
}


vector <string> UPDATE (string str)
{
    vector <string> chizaye_jadid;
    vector <string> kolfile;
    vector <string> kojas;
    vector<string> bakhsh;
    vector<string> khali;
    string esm_jadval = "" , donbal_chi_im = "" , str1="" , str2="";
    int i = 0 ;

    if(str[str.size()-1] != ';')
        cout << "ERROR: ebarat vared shode shamel << ; >> nist." << endl ;
    while (str[i] != ' ')
    {
        esm_jadval += str[i] ;
        i++ ;
    }

    i = i + 1;

    if (str.substr(i,5) != "WHERE")
        cout << "ERROR: ebarat vared shode shamel << WHERE >> nist." << endl ;
    i = i + 6 ;
    while(str[i] != ' ')
    {
        donbal_chi_im += str[i];
        i++ ;
    }
    i = i + 1;
    if (str.substr(i,6) != "VALUES")
        cout << "ERROR: ebarat vared shode shamel << VALUES >> nist." << endl ;
    i = i + 8;
    ifstream schema("schema.txt");
    bool check_kon = false;
    while(!schema.eof())
    {
        getline(schema,str1);
        if(str1 == esm_jadval)
        {
            check_kon = true ;
            break;
        }
    }

    if (!check_kon)
    {
        cout << "ERROR: chenin jadvali vojod nadarad. " << endl;
        return khali;
    }
    str = str.substr(i,str.size()-i-2);
    chizaye_jadid = sharhe_sharhe_kon(str,',');
    ofstream makefile((esm_jadval+".txt").c_str(),ios::app);
    makefile.close();
    int q = 0 ;
    getline(schema,str);
    while (str !="")
    {
        bakhsh = sharhe_sharhe_kon(str, ' ');
        if(q >= chizaye_jadid.size())
        {
            cout<<"ERROR: mizan motagheir haye vared shode bish az had mojaz ast." << endl;
            return khali;
        }
        if (bakhsh.size() == 2)
        {
            if(!typesho_check_kon(chizaye_jadid[q],bakhsh[1]))
            {
                cout << "ERROR: type vorodi haye vared shode ba type file schema moghayerat darad. " << endl;
                return khali;
            }
        }

        if (bakhsh.size() == 3)
        {
            if(!typesho_check_kon(chizaye_jadid[q],bakhsh[2]))
            {
                cout << "ERROR: type vorodi haye vared shode ba type file schema moghayerat darad. " << endl;
                return khali;
            }
        }
        q++ ;
        getline(schema,str);
    }


    schema.close();
    if( q != chizaye_jadid.size())
    {
        cout << "ERROR: mizan motagheir haye vared shode bish az had mojaz ast." << endl ;
        return khali;
    }

    kojas = kodom_khate(donbal_chi_im , esm_jadval);
    bool yektas = update_check_kon(esm_jadval ,donbal_chi_im, chizaye_jadid);
    if (!yektas)
    {
        cout << "ERROR: ebarat vared shode yekta nist" << endl;
        return khali;
    }

    ifstream fileghabli ((esm_jadval+".txt").c_str());
    while(!fileghabli.eof())
    {
        getline(fileghabli,str2);
        kolfile.push_back(str2);
    }
    fileghabli.close();
    int temp = 0;
    ofstream filejadid ((esm_jadval+".txt").c_str());

    for(int a = 0 ; a < kolfile.size() ; a++)
    {
        for(int b = 0 ; b < kojas.size() ; b++)
        {
            if(kolfile[a]==kojas[b])
                temp += 1;
        }
        if(temp == 0)
        {
            filejadid << kolfile[a];
            if(kolfile.size()-1 != a)
                    filejadid << endl;
        }
        if(temp == 1)
        {
            for(int c=0 ; c < chizaye_jadid.size() ; c++)
            {
                filejadid << chizaye_jadid[c];
                if(chizaye_jadid.size()-1 != c)
                    filejadid << ' ';
            }
            filejadid<<endl;
        }
        temp = 0;

    }
    return chizaye_jadid;
}


bool update_check_kon( string jadval ,string donbal_chi_im, vector<string> chizaye_jadid)
{
    bool check_kon = false ;
    bool natije = true ;
    bool barahamishe_khodafez = true;
    int q = 0;
    string yekta ="" , str="";
    vector <string> kojas = kodom_khate(donbal_chi_im , jadval);
    vector <string> khali ;
    ifstream schema("schema.txt");
    while(!schema.eof())
    {
        getline(schema,str);
        if(str == jadval)
        {
            check_kon = true ;
            break;
        }
    }
    if (!check_kon)
    {
        cout << "ERROR: chenin jadvali dar file schema vojod nadarad. " << endl;
        return false;
    }
    getline(schema,str);
    while (str !="")
    {
        vector<string> bakhsh = sharhe_sharhe_kon(str, ' ');
        if(bakhsh.size() == 3)
        {
            ifstream filemon1((jadval+".txt").c_str());
            while(!filemon1.eof())
            {
                getline(filemon1,yekta);
                vector <string> yektaii;
                if(yekta=="")
                    break;
                yektaii = sharhe_sharhe_kon(yekta,' ');
                for(int p=0 ; p<kojas.size() ; p++)
                {
                    if(yekta == kojas[p])
                    {
                        natije = false;
                        break;
                    }
                }
                if((yektaii [q] == chizaye_jadid[q]) && (natije))
                {
                    //cout<< "ERROR: ebarat vared shode yekta nist" << endl;
                    barahamishe_khodafez = false;
                    break;
                }

            }
            filemon1.close();
        }
        q++ ;
        natije = true;
        getline(schema,str);
    }
    return barahamishe_khodafez  ;
}




