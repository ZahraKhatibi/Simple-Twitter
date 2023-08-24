#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
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
void account_besaz();
void boro_to_account();
void tweet_bezaram();
void tweet_bekhonam();
void tweeto_che_konim();
string str_kon(int integer);
int int_bekon(string str);
string timeo_khoshgel_kon(char* dt);
vector<string> database(string stri);
void khoshgel_chap_kon(vector<string> str);
string tweet_chap_kon(string str);
void taghir();

string chi_amr_mikonid="" , alan_ki_injast = "" , name_alan_ki_injas="";
int id_alan_ki_injast = 0 ;
int password_alan_ki_injast = 0 ;
bool hasti_ya_na = false;



int main ()
{
    int vorod;
    while(true)
    {
        if(hasti_ya_na)
        {
            cout <<"chikar mikhay koni? " << endl
                << "1. mikham tweet konam bezaram " << endl
                << "2. mikham tweet mardomo bebinam " << endl
                << "3. mikham atelaAtam ro taghir bedam " << endl 
                << "4. khaste shodam az accountam mikham beram biron" << endl ;

            cin >> vorod;
            switch(vorod)
            {
                case 1: tweet_bezaram(); break;
                case 2: tweet_bekhonam(); break;
                case 3: taghir(); break;
                case 4: hasti_ya_na = false; break;
            }
        }

        else
        {
            cout << "chikar mikhay koni? " << endl
                << "1. mikham beram to accountam " << endl
                << "2. mikham account besazam " << endl
                << "3. hichi baba beband barname ro badesham uninstall kon ba in appet" << endl ;
            cin >> vorod;
            switch (vorod)
            {
                case 1: boro_to_account(); break;
                case 2: account_besaz(); break;
                case 3: return 0 ;
            }
        }
   }
}


vector<string> database(string stri)
{
   vector<string> khali;
   //stri="~$ UPDATE FROM users WHERE name==za VALUES (2,zahra1,mahyar12,123456);";
   //getline(cin , stri );
    if (stri.substr(0,2) == "~$")
    {
        if (stri.substr(3,11) == "INSERT INTO")
            INSERT(stri.substr(15,stri.size()-15));

        else if (stri.substr(3,11)=="SELECT FROM")
            khali = SELECT(stri.substr(15,stri.size()-15));

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
    // for(int i=0;i<khali.size();i++)
    // {
    //     cout<<khali[i]<<endl;
    // }       

    return khali;
}


void account_besaz()
{
    vector<string> r1 ;
    vector<string> r2 ;
    string name , username ;
    int password1 , password2 ;
    int id=0;
    cout << "esmet chie? " <<endl ;
    cin >> name;
    cout<< "dost dari usernamet chi bashe? " <<endl ;
    cin >> username;
    cout << "ramzet ro vared kon: " <<endl;
    cin >> password1;
    cout << "ye bar dige passwordeto vared kon bebinam baldi ya na: " << endl;
    cin >> password2;
    if (password1 != password2)
        account_besaz();
    else
    {
        time_t now = time(0);
        char *keyomadi ;
        keyomadi = ctime(&now);
        chi_amr_mikonid = "~$ SELECT FROM users;";
        r1 = database(chi_amr_mikonid);
        if(r1.size() == 0)
            id = 1;
        else if(r1.size() != 0)
        {
            r2 = sharhe_sharhe_kon(r1[r1.size() - 2] , ' ');
            id = int_bekon(r2[0]) + 1;
        }
        chi_amr_mikonid = "~$ INSERT INTO users VALUES (" + str_kon(id) + "," + name + "," + username + "," + str_kon(password1) + "," + timeo_khoshgel_kon(keyomadi) + ",0);";
        database(chi_amr_mikonid);
    }
}


void boro_to_account()
{
    string  username ;
    int password;
    vector<string> r1;
    vector<string> r2;
    cout << "ba che esmi join shodi ghablan? "<< endl;
    cin >> username;
    cout << "passwordet chie? " << endl ;
    cin >> password;
    chi_amr_mikonid = "~$ SELECT FROM users WHERE username==" + username + ";";
    r1 = database(chi_amr_mikonid);
    if(r1.size() == 0 )
    {
        cout << "chenin usernami sabt nashode ast." << endl;
        boro_to_account();
    }
    r2 = sharhe_sharhe_kon(r1[0],' ');
    if (r2[3]==str_kon(password))
    {
        alan_ki_injast = username;
        id_alan_ki_injast = int_bekon(r2[0]);
        name_alan_ki_injas = r2[1];
        password_alan_ki_injast = int_bekon(r2[3]);
        hasti_ya_na = true;
    }
    else
    {
        cout << "password ya usernamet ro eshtebah zadi, ye bar dige emtehan kon " << endl;
        boro_to_account();
    }
}


void tweet_bezaram()
{
    vector<string> r1;
    vector<string> r2;
    vector<string> r3;
    string tweet;
    int id=0;
    cout << "tweetet ro vared kon : " << endl;
    // cin.ignore();
    // getline(cin, tweet);
    cin>>tweet;
    time_t now = time(0);
    char* keygozashti = ctime(&now);
    chi_amr_mikonid = "~$ SELECT FROM tweets;";
    r1 = database(chi_amr_mikonid);
    if(r1.empty())
        id = 1;
    else if(r1[0]=="")
        id=1;
    else
    {
        r2 = sharhe_sharhe_kon(r1[r1.size() - 2] , ' ');
        id = int_bekon(r2[0]) + 1;
    }
    chi_amr_mikonid = "~$ INSERT INTO tweets VALUES (" + str_kon(id)+ ","+ alan_ki_injast + ",0,0," + timeo_khoshgel_kon(keygozashti) + ","+ tweet + ",0);";
    database(chi_amr_mikonid);
    chi_amr_mikonid = "~$ SELECT FROM users WHERE username=="+alan_ki_injast+';';
    r3=sharhe_sharhe_kon(database(chi_amr_mikonid)[0],' ');
    chi_amr_mikonid = "~$ UPDATE FROM users WHERE username==" + alan_ki_injast + " VALUES ("+r3[0]+","+r3[1]+","+r3[2]+","+ r3[3]+","+r3[4]+","+r3[5]+"-"+str_kon(id)+");";
    database(chi_amr_mikonid);
}


void tweet_bekhonam()
{
    vector<string> r1;
    vector<string> r2;
    vector<string> r3;
    string username;
    int che_konim;
    cout<< "mikhay bar che asasi tweet bekhoni? "<< endl
        << "1. harchi dari biyar" << endl
        << "2. tweetay shakhs khasi mad nazarame" <<endl
        << "3. tweetaye khodamo biyar" << endl ;

    cin >> che_konim;
    switch (che_konim)
    {
        case 1:
        {
            chi_amr_mikonid = "~$ SELECT FROM tweets;";
            r1 = database(chi_amr_mikonid);
            khoshgel_chap_kon(r1);
            cout <<endl;
            tweeto_che_konim();
            break;
        }
        case 2:
        {
            cout << "khob bego bebinam tweet ki ro mikhay? ";
            cin >> username;
            chi_amr_mikonid = "~$ SELECT FROM tweets WHERE username==" +username + ";" ;
            r2 = database(chi_amr_mikonid);

            khoshgel_chap_kon(r2);
            cout << endl ;
            tweeto_che_konim();
            break;
        }

        case 3:
        {
            chi_amr_mikonid = "~$ SELECT FROM tweets WHERE username==" + alan_ki_injast +";" ;
            r3 = database(chi_amr_mikonid);
            khoshgel_chap_kon(r3);
            cout << endl ;
            tweeto_che_konim();
            break;
        }
    }
}


void tweeto_che_konim()
{
    vector <string> r1;
    vector <string> r2;
    vector <string> r3;
    vector <string> r4;
    vector <string> r5;
    vector <string> r6;
    int id_tweet , che_konim= 0 , retweet_bodan = 0;
    cout << "kamele kodom tweet ro mikhay? id on ro vared kon" << endl;
    cin >> id_tweet ;
    chi_amr_mikonid = "~$ SELECT FROM tweets WHERE tweet_id==" + str_kon(id_tweet) +";";
    r1 = database(chi_amr_mikonid);
    r2 = sharhe_sharhe_kon(r1[0],' ');

    cout<< " << " << tweet_chap_kon(r2[5])  << " >> " << " || POSTED BY: "<< r2[1] <<"||" ;
    if(r2[2]!="0") 
        cout<<"(RETWEET FROM : " << r2[2] << ") || " ;
    cout <<" AT: " << r2[4] <<endl<<"|| COMMENTS: " ;

    r5 = sharhe_sharhe_kon(r2[6],'-');

    for(int i=1 ; i < r5.size() ; i++)
    {
        chi_amr_mikonid = "~$ SELECT FROM comments WHERE comment_id=="+r5[i]+";";
        r6 = database(chi_amr_mikonid);
        cout <<tweet_chap_kon(sharhe_sharhe_kon (r6[0],' ')[4]) << "  || BY: " << sharhe_sharhe_kon (r6[0],' ')[1] << endl;
    }

    cout << endl;
    cout<< "dos dari ba in tweet chikar koni? " << endl
        << "1. mikham likesh konam" << endl
        << "2. mikham retweetesh konam" << endl
        << "3. mikham like hasho bebinam" << endl
        << "4. mikham barash comment bezaram" << endl;

    cin >> che_konim ;
    switch (che_konim)
    {
       case 1:
        {
            chi_amr_mikonid = "~$ UPDATE FROM tweets WHERE tweet_id=="+ r2[0] +" VALUES ("+r2[0]+","+r2[1]+","+r2[2]+","+r2[3]+"-"+str_kon(id_alan_ki_injast)+"," + r2[4]+","+(r2[5]) +","+ r2[6]+");";
            database(chi_amr_mikonid);
            break;
        }

        case 2:
        {
            int id = 0 ;
            time_t now = time(0);
            char* keygozashti = ctime(&now);
            chi_amr_mikonid = "~$ SELECT FROM tweets;";
            r3 = database(chi_amr_mikonid);
            r3 = sharhe_sharhe_kon(r3[r3.size() - 2] , ' ');
            id = int_bekon(r3[0]) + 1;
            chi_amr_mikonid = "~$ INSERT INTO tweets VALUES (" + str_kon(id) +","+ alan_ki_injast +"," +str_kon(id_tweet) + ",0," + timeo_khoshgel_kon(keygozashti) + "," + (r2[5])+","+r2[6]+");";
            database(chi_amr_mikonid);

            chi_amr_mikonid = "~$ SELECT FROM users WHERE username==" + alan_ki_injast +";";
            r3 = database(chi_amr_mikonid);
            r3 = sharhe_sharhe_kon(r3[0],' ');
            chi_amr_mikonid = "~$ UPDATE FROM users WHERE username==" + alan_ki_injast + " VALUES ("+ r3[0]+","+ r3[1] +","+r3[2] +"," + r3[3] +","+ r3[4]+","+r3[5]+"-"+str_kon(id)+");";
            database(chi_amr_mikonid);
            break;
        }

        case 3:
        {
            cout<<"LIKED BY :"<<endl;
            vector<string> like;
            chi_amr_mikonid = "~$ SELECT FROM tweets WHERE tweet_id=="+ str_kon(id_tweet)+";";
            r3 =database(chi_amr_mikonid);
            r3 = sharhe_sharhe_kon(r3[0],' ');
            like = sharhe_sharhe_kon(r3[3],'-');
            if(like.size() == 1)
                cout << "hishki likesh nakarde :(" << endl;

            for(int a=1 ; a<like.size() ; a++)
            {
                chi_amr_mikonid = "~$ SELECT FROM users WHERE id=="+ like[a]+";";
            }
            break;
        }

        case 4:
        {
            time_t now = time(0);
            char* keygozashti = ctime(&now);
            string comment;
            cout << "matn commentet ro vared kon: "  << endl ;
            cin >> comment ; 
            int id_comment = 0;
            chi_amr_mikonid = "~$ SELECT FROM comments;";
            r3 = database(chi_amr_mikonid);
            if(r3.empty())
            {
                id_comment = 1;
            }
            else if(r3[0]=="")
            {
                id_comment = 1;
            }
            else
            {
                r4 = sharhe_sharhe_kon(r3[r3.size()-2],' ');
                id_comment = int_bekon(r4[0]) + 1;
            }
            chi_amr_mikonid = "~$ INSERT INTO comments VALUES ("+ str_kon(id_comment) + "," + alan_ki_injast +","+ str_kon(id_tweet)+"," + timeo_khoshgel_kon(keygozashti)+","+ comment+");" ;
            database(chi_amr_mikonid);
            chi_amr_mikonid  = "~$ UPDATE FROM tweets WHERE tweet_id==" + str_kon(id_tweet) + " VALUES ("+ str_kon(id_tweet) +","+ r2[1] +","+r2[2] +"," + r2[3]+ "," +r2[4] +","+r2[5]+"," + r2[6]+"-"+ str_kon(id_comment)+");" ;
            database(chi_amr_mikonid);
            break ; 
            
        }
    }
}

void taghir()
{
    vector<string> r1;
    vector<string> r2;
    int halat;
    cout<< "mikhay chi ro taghir bedi? " << endl 
        << "1. esmam ro mikham taghir bedam" << endl 
        << "2. usernamam ro mikham taghir bedam" << endl 
        << "3. passwordam ro mikham taghir bedam " << endl ;
    cin >> halat ;
    chi_amr_mikonid = "~$ SELECT FROM users WHERE username==" + alan_ki_injast + ";";
    r1 = database(chi_amr_mikonid);
    r2 = sharhe_sharhe_kon(r1[0],' ');
    switch (halat)
    {
        case 1: 
        {
            string esm;
            cout << "esm jadidet ro vard kon : " << endl;
            cin >> esm;
            chi_amr_mikonid = "~$ UPDATE FROM users WHERE username==" + alan_ki_injast + " VALUES ("+r2[0]+","+esm+","+r2[2]+","+ r2[3]+","+r2[4]+","+r2[5]+");" ;
            database(chi_amr_mikonid);
            break;
        }

        case 2:
        {
            string username;
            cout << "username jadidet ro vard kon : " << endl;
            cin >> username;
            chi_amr_mikonid = "~$ UPDATE FROM users WHERE username==" + alan_ki_injast + " VALUES ("+r2[0]+","+r2[1]+","+username+","+ r2[3]+","+r2[4]+","+r2[5]+");" ;
            database(chi_amr_mikonid);
            break;
        }

        case 3:
        {
            string password;
            cout << "password jadidet ro vard kon : " << endl;
            cin >> password;
            chi_amr_mikonid = "~$ UPDATE FROM users WHERE username==" + alan_ki_injast + " VALUES ("+r2[0]+","+r2[1]+","+r2[2]+","+ password +","+r2[4]+","+r2[5]+");" ;
            database(chi_amr_mikonid);
            break;
        }
    }
}


string timeo_khoshgel_kon(char*dt)
{
   string time = "";
   for (int i = 0 ; i < 24 ; i++)
   {
      if(dt[i] == ' ')
         dt[i] = '/';
      time += dt[i];
   }
   return time;
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
    while(str[i]!=' ')
    {
        esm_jadval += str[i];
        i++;
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
            cout<<chio_hazf_konam[a]<<"="<<str<<endl;

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


int int_bekon(string str)
{
    string dict="0123456789";
    int a=0;
    for(int b=0 ; b<str.size() ; b++)
    {
        for(int i=0;i<10;i++){
            if(dict[i]==str[b])
                a = (a*10) + i ;
        }
    }
    return a;
}


string str_kon(int integer)
{
    string a="";
    while(integer>0)
    {

        a =  "0123456789"[integer%10] + a;
        integer = integer / 10;
    }
    return a;
}


void khoshgel_chap_kon(vector<string> str)
{
    vector<string> r1;
    for(int a=0 ; a<str.size() ; a++)
    {
        if(str[a]!="")
        {
            r1 = sharhe_sharhe_kon(str[a],' ');

            cout << "ID: " << r1[0] << "    " << "USERNAME: " << r1[1] << "    " << "LIKED BY "<< sharhe_sharhe_kon(r1[3],'-').size()-1 << " MEMBERS"<< "    " << tweet_chap_kon( r1[5].substr(0,10)) <<"...more" <<"    "<< "POSTED AT: " <<r1[4] <<endl ; 
        }
    }
}


string tweet_chap_kon(string str)
{
    string khshgel = "";
    for(int a=0 ; a<str.size() ; a++)
    {
        if(str[a]=='/')
            str[a]= ' ';
        khshgel+= str[a];
    }
    return khshgel;
}