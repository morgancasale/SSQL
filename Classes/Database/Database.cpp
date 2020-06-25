#include "Database.h"


bool Database::check_TableName(const string & name){
    bool noErr=true;
    for(string tmp: allowed_coms){ noErr=(name!=tmp); }
    if(noErr){ for(const string & tmp: allowed_types){ noErr=(name!=tmp); } }
    if(noErr){ for(const string & tmp: reserved_words){ noErr=(name!=tmp); } }
    return noErr;
}

//if check_existence parameter is true the function checks if the table exists, else, if the function doesn't exist
bool Database::check_Table_existence(const string &in_Table_name, const bool & check_existence){
    bool not_exists=true;
    int i=0;
    if(!Tables.empty()) {
        do {
            string tmp=Tables[i].get_name();
            string in_Table_nameCopy=in_Table_name;
            if ( tolower(tmp) == tolower(in_Table_nameCopy)) {
                not_exists = false;
            }
            i++;
        } while ((i < Tables.size()) and not_exists);
    }

    if(check_existence){ //devo controllare che esista la tabella
        if(not_exists){ //la tabella non esiste
            cerr<<endl<<"Table named "<<in_Table_name<<" doesn't exist!"<<endl;
        }
    }
    if(!check_existence){ //devo controllare se la tabella non esista
        if(!not_exists){ //la tabella esiste
            cerr<<endl<<"Table named "<<in_Table_name<<" already exists!"<<endl;
            cerr<<"Choose another name.";
        }
    }

    return not_exists;
}

bool Database::process_command(string choice) {
    bool noErr=true;  int j=0;
    string command=take_command(choice);
    if(command=="quit()"){
        QUIT();
    } else
    if(command=="create table"){
        if(!control_create(choice)){
            cerr<<endl<<"CREATE command syntax error!";
            noErr=false;
        } else{
            noErr = CREATE_TABLE(choice);
        }
    } else
    if(command=="drop table"){
        if((noErr=control_drop(choice))){
            noErr=DROP_TABLE(choice);
        }
    } else
    if(command=="truncate table" and control_truncate(choice)){
        if((noErr=control_truncate(choice))){
            noErr=TRUNCATE_TABLE(choice);
        }
    } else
    if(command=="insert into") {
        if((noErr=control_insert(choice))){
            noErr=!INSERT_INTO(choice);
        }
    } else
    if(command=="delete"){
       if((noErr=control_delete(choice))){
           noErr=DELETE(choice);
       }
    } else
    if(command=="update"){
        if((noErr=control_update(choice))){
            noErr=UPDATE(choice);
        }
    } else
    if(command=="select"){
        PRINT(choice);
    }
    return noErr;
}
bool Database::check_command(const string &input, const bool &show_error, string &command) { //checks whatever the command exists
    bool err=true;
    for(const string &tmp :allowed_coms){ //this loop checks if in the input string there's an allowed command, and if found writes it in the variable "command"
        if(((command= substrcc(input, 0, 1, ' ')) == tmp) or ((command= substrcc(input, 0, 2, ' ')) == tmp)){
            err=false;
        }
    }
    if(show_error and err){
        cerr<<"This command doesn't exist!";
    }
    return err;
}

bool Database::INSERT_INTO(string in){
    bool err;

    string TableName= substrcc(in, 0, 1, ' ', '(');
    in-=TableName;
    replace_chars(TableName, {' '}, -1);
    int Table_i=find_Table(TableName);

    if(Table_i!=-1) {
        Table & table = Tables[Table_i];
        //Column<string> & col=(*static_cast<Column<string> *>(table.cols[0]));
        Table tableBackup=table;

        vector<string> elementsNames;
        vector<string> elementsValues;
        err=!get_INSERT_INTO_data(in, elementsNames, elementsValues);

        if(!err){ err=Tables[Table_i].set_INSERT_INTO_data(elementsNames, elementsValues); }
        if(!err){
            err= Tables[Table_i].checkINSERT_INTOData_and_Nullify(elementsNames);
        }
        if(!err and !table.ForeignCols.empty()){ err=!checkForeignKeys(table); }
        if(!err){
            Tables[Table_i].auto_increment_col();
        }
        Tables[Table_i].rows++;

        if(err){
            table=tableBackup;
        }
    } else{
        cerr << endl << "There is no Table with name " << TableName << "!";
        err=true;
    }
    return err;
}

bool Database::get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues) {
    bool noErr=true;
    for(; !substrcc(in, 1, 1, '(', ')').empty();){
        string elementName= substrcc(in, 1, 1, '(', ',');
        if(elementName=="/err" or num_of_words(elementName)>1){
            elementName= substrcc(in, 1, 1, '(', ')');
            erase_substr(in, elementName);
        }else{
            erase_substr(in, elementName+", ");
        }
        replace_chars(elementName, {' '}, -1);
        elementsNames.push_back(elementName);
    }

    in-="() values (";
    for(int i=0; !substrcc(in, 0, 1, ' ', ')').empty() and noErr; i++){
        string elementValue= substrcc(in, 0, 1, ' ', ',');
        if(elementValue=="/err"){
            elementValue= substrcc(in, 0, 1, ' ', ')');
            erase_substr(in, elementValue);
        }else{
            erase_substr(in, elementValue+", ");
        }
        for(const string & tmp: reserved_words){ if(elementValue==tmp){ noErr=false; } }
        if(noErr){
            elementsValues.push_back(elementValue);
        } else{
           cerr<<endl<<"A reserved word ( "<<elementValue<<" ) was inserted!";
        }
    }
    return noErr;
}

bool Database::checkForeignKeys(const Table &table, int row) {
    bool noErr=true;
    for(int i=0; i<table.ForeignTables.size() and noErr; i++){
        Table & ForeignTable=Tables[table.ForeignTables[i]];
        int FCol_i=table.ForeignCols[i], ConCol_i=table.ConnectedCols[i];
        string type;
        if((type=ForeignTable.elementsTypes[FCol_i])==table.elementsTypes[ConCol_i]){
            noErr=false;
            if(type=="int"){
                const Column<int> & FCol=(*static_cast<Column<int>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<int> & ConCol=(*static_cast<Column<int>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const int & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }
            if(type=="float"){
                const Column<float> & FCol=(*static_cast<Column<float>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<float> & ConCol=(*static_cast<Column<float>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const float & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }
            if(type=="char"){
                const Column<char> & FCol=(*static_cast<Column<char>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<char> & ConCol=(*static_cast<Column<char>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const char & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }
            if(type=="string" or type=="text"){
                const Column<string> & FCol=(*static_cast<Column<string>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<string> & ConCol=(*static_cast<Column<string>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const string & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }
            if(type=="date"){
                const Column<Date> & FCol=(*static_cast<Column<Date>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<Date> & ConCol=(*static_cast<Column<Date>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const Date & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el.Date_to_string()<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }
            if(type=="Time"){
                const Column<Time> & FCol=(*static_cast<Column<Time>*>(ForeignTable.cols[table.ForeignCols[i]]));
                const Column<Time> & ConCol=(*static_cast<Column<Time>*>(table.cols[table.ConnectedCols[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const Time & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cerr<<endl<<"The element "<<ConCol_el.to_string()<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.get_name()<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.get_name()<<"!";
                }
            }


        } else{
            cerr<<endl<<"The types of the Foreign column and the Connected one don't match!";
        }
    }
    return noErr;
}

int Database::find_Table(string in) {
    int i=0;
    bool found=false;
    for(; i<Tables.size() and !found; i++){
        string tmp=Tables[i].get_name();
        if(tolower(tmp)==tolower(in)){
            found=true;
        }
    }
    if(!found){
        return -1;
    } else{
        return i-1;
    }
}

bool Database::DELETE(string in) {
    string table_name= substrcc(in, 0, 1);
    bool noErr=!check_Table_existence(table_name, true);
    int table_i=find_Table(table_name);

    if(noErr) {
        string element = substr_from_s_to_s(in,"where ","=");
        replace_chars(element, {' '}, -1);
        int col_i;
        if ((col_i=Tables[table_i].get_col_index(element))==-1) {
            cerr<<"No colum with name "<<element<<" was found!";
            noErr = false;
        }
        if(noErr){
            string data = substrcc(in, 1, 1, '=', ';');
            vector<int> foundRows;
            noErr=Tables[table_i].find_Rows_by_value(data, col_i, foundRows);
            if(noErr){
                Tables[table_i].deleteRows(foundRows);
            }
        }

    }
    return noErr;
}

bool Database::DROP_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cerr<<endl<<"No Table named "<<tableName<<" was found!";
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];
        for(int i=table.elementsTypes.size(); i>0; i--){
            table.clear_col(i);
            table.elementsTypes.resize(table.elementsTypes.size()-1);
        }
        deleteElements_from_vec(Tables,{Table_i});
    }
    return noErr;
}

bool Database::TRUNCATE_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cerr<<endl<<"No Table named "<<tableName<<" was found!";
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];
        table.empty_content();
    }
    return noErr;
}

bool Database::UPDATE(string in){
    bool noErr;
    string tableName= substrcc(in, 0, 1);
    noErr=!check_Table_existence(tableName, true);
    Table & table=Tables[find_Table(tableName)];
    Table TableBackup=table;

    if(noErr){
        in-=(tableName+" set ");

        string colToSearch= substr_from_s_to_s(in, "where ", "=", true);
        replace_chars(colToSearch, {' '}, -1);
        int col_index;
        noErr=((col_index=table.get_col_index(colToSearch))!=-1);

        if(noErr){
            string searchData= substr_from_s_to_s(in, colToSearch, ";");
            searchData= substrcc(searchData, 1, -1, '=', ' ');
            replace_chars(searchData, {' '}, -1);

            vector<int> foundRows;
            noErr=table.find_Rows_by_value(searchData, col_index, foundRows);
            in-=(substr_from_s_to_s(in, " where", ";")+";");
            if(noErr){
                replace_chars(in, {' '}, -1);
                vector<string> updateData;
                while( !in.empty() ){
                    string tmp= substrcc(in, 0, 1, ' ', ',');
                    tmp+=",";
                    if(tmp=="/err,"){
                        tmp= substrcc(in, 0, -1);
                    }
                    in-=tmp;
                    if(tmp.find(',')){ tmp-=","; }
                    updateData.push_back(tmp);

                }
                noErr= table.set_UPDATE_data(updateData, foundRows);

                if(noErr and !table.ForeignTables.empty()){ noErr=checkForeignKeys(table, foundRows[0]); }
            } else{
                cerr<<"No row containing"<<searchData<<"was found!";
            }

        } else{
            cerr<<endl<<"No column "<<colToSearch<<"was found!";
        }

    } else{
        cerr<<"Table named "<<tableName<<" doesn't exist!";
    }

    if(!noErr){
        table=TableBackup;
    }
    return noErr;
}

bool Database::PRINT(string in) {
    bool noErr;
    string tableName = take_the_next_word(in, "from");
    noErr = !check_Table_existence(tableName, true);
    Table &table = Tables[find_Table(tableName)];
    if(noErr){
        //SELECT ID,	AGE,	SALARY		FROM CUSTOMERS	WHERE	AGE	=	20;
        vector <string> colNames;
        string tmp;
        bool exit=true;
        do{
            tmp= substrcc(in, 0, 1, ' ', ',');
            if(tmp=="/err") {
                tmp=in.substr(0,in.find("from")-1);
                if(num_of_words(tmp)==1) {
                    in-=(tmp+" ");
                    colNames.push_back(tmp);
                }else  {
                    exit=false;
                }
            }
            else {
                in-=(tmp+","+" ");
                colNames.push_back(tmp);
            }
        }while(exit);

        if(in.find("*")!=in.npos){
            table.printCols({"*"});
        }else if(in.find("where")!=in.npos){
            table.printCols(colNames, take_the_next_word(in,"where"), take_the_next_word(in,"="));
        }else{
            table.printCols(colNames);
        }
    }
    return noErr;
}

void Database::QUIT(){
    ofstream out;
    out.open("../Database.txt", ios::trunc);
    for(Table & table:Tables){
       table.printTable_to_file(out);
       out<<endl;
    }
    out<<"|";
    out.close();
}

bool Database::START() {
    bool noErr;
    ifstream in;
    in.open("../Database.txt", ios::in);
    if(!in){
        cerr<<endl<<"The file doesn't exist!";
    }
    string line;
    int i=0;
    char end=42;
    while(end!='|'){
        getline(in, line);
        this->Tables.resize(i+1);
        this->Tables[i].createTable_from_file(in, line);
        i++;
        getline(in, line);
        end=line[0];
        if(end!='|'){
            streampos tmp = in.tellg();
            getline(in, line);
            if(line[0]=='|'){
                end=line[0];
            } else{
               in.seekg(tmp);
            }
        }
    }
    return noErr;
}

bool Database::CREATE_TABLE(string in){
    bool noErr=true;
    string table_name= substrcc(in, 0, 1);
    noErr=check_TableName(table_name);
    if(check_Table_existence(table_name, false) and noErr){
        Table temp;//this creates a temporary Table

        string foreignKeys;
        if(in.find("foreign key")!=-1){
            foreignKeys = substr_from_s_to_s(in, "foreign key", ");", false, true);
            in -= ", " + foreignKeys;
        }

        if(temp.set_Table(in)){
            if(!foreignKeys.empty()){
                noErr=setForeignKeys(foreignKeys, temp);
            }
            if(noErr){
                Tables.push_back(temp);
            }
        }
        else{
            noErr=false;
        }
    }
    return noErr;
}

bool Database::setForeignKeys(string data, Table &thisTable) {
    bool noErr=true;
    string line = substrcc(data, 0, 1, ' ', ',');
    while(noErr and !data.empty()) {
        line += ", ";
        if (line == "/err, ") {
            line = substrcc(data, 0, -1);
        }
        data-=line;

        string thisTableElement=substrcc(line, 1, 1, '(', ')');
        int thisCol_i=thisTable.find_col_by_name(thisTableElement);
        if(thisCol_i != -1){
            string foreignTableName = substrcc(line, 4, 5);
            int foreignTable_i = find_Table(foreignTableName);

            if (foreignTable_i != -1){
                Table & foreignTable=Tables[foreignTable_i];

                string foreignTableElement=substrcc(line, 2, 2, '(', ')');
                int foreignCol_i=foreignTable.find_col_by_name(foreignTableElement);

                if(foreignCol_i != -1){
                    thisTable.ForeignTables.push_back(foreignTable_i);
                    thisTable.ConnectedCols.push_back(thisCol_i);
                    thisTable.ForeignCols.push_back(foreignCol_i);
                    line = substrcc(data, 0, 1, ' ', ',');
                } else{
                    cerr<<endl<<"Uncaught reference to a non existence Column in";
                    cerr<<" the foreign Table "<<foreignTableName;
                    cerr<<"! (Column name: " << foreignTableElement<< ")";
                }
            }else {
                cerr << endl << "Uncaught reference to a non existence Table! (Table name: " << foreignTableName << ")";
                noErr=false;
            }
        } else{
            cerr << "No element called " << thisTableElement << " exists in this Table!";
            noErr=false;
        }
    }
    return noErr;
}

bool Database::readCommands_from_file(const string &filepath){
    bool noErr=true;
    ifstream in;
    in.open(filepath, ios::in);
    if(!in){
        cerr<<endl<<"The file "<< filepath <<" doesn't exist!";
        noErr=false;
    }

    if(noErr){
        string line="the cake is a lie", command;
        int line_i=0, startLine_i=0, endLine_i;
        bool start=true;
        while(line!="~" and noErr) {
            command="";
            do{
                if(start){ startLine_i=line_i; start=false;}
                getline(in, line);
                if(line!="~"){
                    if(line=="\r"){
                        getline(in, line);
                        line_i++;
                    }
                    if(line!="~"){
                        replace_chars(line, {'\r'}, -1);
                        command += " " + line;
                        line_i++;
                    }
                }
            } while (line.find(';') == -1 and line!="~");

            if(line!="~"){
                endLine_i = line_i - 1;
                start = true;

                noErr = process_command(command);
                if (!noErr) {
                    if (endLine_i == startLine_i) {
                        cerr << endl << "Error at line " << startLine_i;
                    } else {
                        cerr << endl << "Error from line " << startLine_i
                             << " to line " << endLine_i << "!";
                    }
                }
            }
        }
    }
    return noErr;
}