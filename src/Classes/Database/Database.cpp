#include "Database.h"


bool Database::check_TableName(const string & name){
    bool noErr=true;
    for(const string & tmp: allowed_coms){ noErr=(name!=tmp); }
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
            string tmp=Tables[i].name;
            if ( tmp == in_Table_name) {
                not_exists = false;
            }
            i++;
        } while ((i < Tables.size()) and not_exists);
    }

    if(check_existence){ //devo controllare che esista la tabella
        if(not_exists){ //la tabella non esiste
            cout << RED<<endl<<"Table named "<<in_Table_name<<" doesn't exist!"<<endl << RESET;
        }
    }
    if(!check_existence){ //devo controllare se la tabella non esista
        if(!not_exists){ //la tabella esiste
            cout << RED<<endl<<"Table named "<<in_Table_name<<" already exists!"<<endl << RESET;
            cout << RED<<"Choose another name."<<endl << RESET;
        }
    }

    return not_exists;
}

bool Database::process_command(string choice, bool & quit) {
    bool noErr=true;  int j=0;
    removeSpaces_fromStart_andEnd(choice);
    string command=take_command(choice);

    if(command=="quit()"){
        quit=true;
        QUIT();
    } else
    if(command=="create table"){
        if(!control_create(choice)){
            cout << RED<<endl<<"CREATE command syntax error!"<<endl << RESET;
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
    if(command=="delete from"){
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
        if((noErr=control_select(choice))){
            noErr= SELECT(choice);
        }
    }
    return noErr;
}

/*bool Database::check_command(const string &input, const bool &show_error, string &command) { //checks whatever the command exists
    bool err=true;
    for(const string &tmp :allowed_coms){ //this loop checks if in the input string there's an allowed command, and if found writes it in the variable "command"
        if(((command= substr_CC(input, 0, 1, ' ')) == tmp) or ((command= substr_CC(input, 0, 2, ' ')) == tmp)){
            err=false;
        }
    }
    if(show_error and err){
        cout << RED<<"This command doesn't exist!" << RESET;
    }
    return err;
}*/

bool Database::INSERT_INTO(string in){
    bool err;

    string TableName= substr_CC(in, 0, 1, ' ', '(');
    in-=TableName;
    replace_chars(TableName, {' '}, -1);
    int Table_i=find_Table(TableName);

    if(Table_i!=-1) {
        Table & table = Tables[Table_i];
        Table tableBackup=table;
        int tmp_rows=table.get_rows();

        vector<string> elementsNames;
        vector<string> elementsValues;
        err=!get_INSERT_INTO_data(in, elementsNames, elementsValues);

        if(!err){ err=table.set_INSERT_INTO_data(elementsNames, elementsValues); }
        if(!err){
            err= table.checkINSERT_INTOData_and_Nullify(elementsNames);
        }
        if(!err and !table.get_ForeignCols().empty()){ err=!checkForeignKeys(table); }
        if(!err){
            table.auto_increment_col();
        }
        table.set_rows(tmp_rows+1);

        if(err){
            table=tableBackup;
        }
        updated_TablesNames.push_back(table.name);
    } else{
        cout << RED << endl << "There is no Table with name " << TableName << "!"<<endl << RESET;
        err=true;
    }
    return err;
}

bool Database::get_INSERT_INTO_data(string in, vector<string> &elementsNames, vector<string> &elementsValues) {
    bool noErr=true;
    for(; !substr_CC(in, 1, 1, '(', ')').empty();){
        string elementName= substr_CC(in, 1, 1, '(', ',');
        if(elementName=="/err" or elementName.find('(')!=-1){
            elementName= substr_CC(in, 1, 1, '(', ')');
            erase_substr(in, elementName);
        }else{
            erase_substr(in, elementName+", ");
        }
        replace_chars(elementName, {' '}, -1);
        elementsNames.push_back(elementName);
    }

    in-=substr_CC(in, 0, 2, ' ', '(')+"(";
    for(int i=0; !substr_CC(in, 0, 1, ' ', ')').empty() and noErr; i++){
        string elementValue= substr_CC(in, 0, 1, ' ', ',');
        for(int j=2; character_counter(elementValue,'"')%2 != 0; j++){
            elementValue= substr_CC(in, 0, j, ' ', ',');
        }

        if(elementValue=="/err"){
            elementValue= substr_CC(in, 0, 1, ' ', ')');
            erase_substr(in, elementValue);
        }else{
            erase_substr(in, elementValue+", ");
        }
        for(const string & tmp: reserved_words){ if(elementValue==tmp){ noErr=false; } }
        if(noErr){
            removeSpaces_fromStart_andEnd(elementValue);
            elementsValues.push_back(elementValue);
        } else{
           cout << RED<<endl<<"A reserved word ( "<<elementValue<<" ) was inserted!"<<endl << RESET;
        }
    }
    return noErr;
}

bool Database::checkForeignKeys(const Table &table, int row) {
    bool noErr=true;
    for(int i=0; i<table.get_ForeignTables().size() and noErr; i++){
        Table & ForeignTable=Tables[table.get_ForeignTables()[i]];
        int FCol_i=table.get_ForeignCols()[i], ConCol_i=table.get_ConnectedCols()[i];
        string type;
        if((type=ForeignTable.get_elementsTypes()[FCol_i])==table.get_elementsTypes()[ConCol_i]){
            noErr=false;
            if(type=="int"){
                const Column<int> & FCol=(*static_cast<Column<int>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<int> & ConCol=(*static_cast<Column<int>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const int & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }
            if(type=="float"){
                const Column<float> & FCol=(*static_cast<Column<float>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<float> & ConCol=(*static_cast<Column<float>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const float & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }
            if(type=="char"){
                const Column<char> & FCol=(*static_cast<Column<char>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<char> & ConCol=(*static_cast<Column<char>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const char & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }
            if(type=="string" or type=="text"){
                const Column<string> & FCol=(*static_cast<Column<string>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<string> & ConCol=(*static_cast<Column<string>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const string & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED<<endl<<"The element "<<ConCol_el<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }
            if(type=="date"){
                const Column<Date> & FCol=(*static_cast<Column<Date>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<Date> & ConCol=(*static_cast<Column<Date>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const Date & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED << endl << "The element " << ConCol_el.date_to_string() << " from the Column " << ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }
            if(type=="Time"){
                const Column<Time> & FCol=(*static_cast<Column<Time>*>(ForeignTable.get_cols()[table.get_ForeignCols()[i]]));
                const Column<Time> & ConCol=(*static_cast<Column<Time>*>(table.get_cols()[table.get_ConnectedCols()[i]]));
                if(row==-1){ row=(int)ConCol.values.size()-1; }
                const Time & ConCol_el=ConCol.values[row];
                for(int j=0; j<FCol.values.size() and !noErr; j++){
                    if(FCol.values[j]==ConCol_el){ noErr=true; }
                }
                if(!noErr){
                    cout << RED<<endl<<"The element "<<ConCol_el.to_string()<<" from the Column "<<ConCol.key
                        <<" ,of the Table "<<table.name<<","<<endl<<"wasn't found in the Column "
                        <<FCol.key<<" of the Table "<<ForeignTable.name<<"!"<<endl << RESET;
                }
            }


        } else{
            cout << RED<<endl<<"The types of the Foreign column and the Connected one don't match!"<<endl << RESET;
        }
    }
    return noErr;
}

int Database::find_Table(const string & in) {
    int i=0;
    bool found=false;
    for(; i<Tables.size() and !found; i++){
        string tmp=Tables[i].name;
        if(tmp==in){
            found=true;
        }
    }
    if(!found){
        return -1;
    } else{
        return i-1;
    }
}

bool Database::DELETE(const string & in) {
    string table_name= substr_CC(in, 0, 1);
    bool noErr=!check_Table_existence(table_name, true);
    int table_i=find_Table(table_name);

    if(noErr) {
        string element = take_the_N_nextWords(in, "where", 1);
        Table & table=Tables[table_i];
        if(!table.get_Foreign_linked()) {
            int col_i;
            if ((col_i = table.get_col_index(element)) == -1) {
                cout << RED << "No colum with name " << element << " was found!" << endl << RESET;
                noErr = false;
            }
            if (noErr) {
                string oper = take_the_N_nextWords(in, "where", 2);
                string data1 = substr_SS(in, oper, ";"), data2 = "/err";
                if (oper == "between") {
                    data1 = substr_SS(in, "between", "and");
                    data2 = substr_SS(in, "and", ";");
                }
                removeSpaces_fromStart_andEnd(data1);
                removeSpaces_fromStart_andEnd(data2);

                vector<int> foundRows;
                noErr = table.find_Rows_by_value(data1, col_i, foundRows, oper, data2);
                if (noErr) {
                    table.deleteRows(foundRows);
                }
                updated_TablesNames.push_back(table.name);
            }
        } else{
            noErr = false;
            cout<<RED<<"Table "<<table.name<<" is referenced somewhere by a Foreign Table!"<<RESET<<endl;
        }

    }
    return noErr;
}

bool Database::DROP_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cout << RED<<endl<<"No Table named "<<tableName<<" was found!"<<endl << RESET;
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];

        if(!table.get_Foreign_linked()){
            for(const int & for_Table_i : table.get_ForeignTables()){
                Table & for_Table=Tables[for_Table_i];
                for_Table.set_Foreign_linked(false);
            }

            vector<string> el_types = table.get_elementsTypes();
            for (unsigned int i = table.get_elementsTypes().size() - 1; i > 0; i--) {
                table.delete_col(i);
            }

            deleted_TablesNames.push_back(table.name);
            deleteElements_from_vec(Tables, {Table_i});
        } else{
            noErr=false;
            cout<<RED<<"You can't Drop a Table connected to others!"<<RESET<<endl;
        }
    }
    return noErr;
}

bool Database::TRUNCATE_TABLE(const string & in){
    bool noErr=true;
    string tableName=in-";";
    noErr=!check_Table_existence(tableName, true);
    if(!noErr){
        cout << RED<<endl<<"No Table named "<<tableName<<" was found!"<<endl << RESET;
    } else{
        int Table_i=find_Table(tableName);
        Table & table=Tables[Table_i];
        if(!table.get_Foreign_linked()) {
            table.empty_Tablecontent();
            updated_TablesNames.push_back(table.name);
        } else{
            noErr=false;
            cout<<RED<<"You can't Empty a Table connected to others!"<<RESET<<endl;
        }
    }
    return noErr;
}

bool Database::UPDATE(string in){
    bool noErr;
    string tableName= substr_CC(in, 0, 1);
    noErr=!check_Table_existence(tableName, true);
    Table & table=Tables[find_Table(tableName)];
    Table TableBackup=table;

    if(noErr){
        in-=(tableName+" set ");
        string oper = take_the_N_nextWords(in, "where", 2), data2between="/err";
        if(oper=="between") data2between=substr_SS(in,"between",";");
        string colToSearch= take_the_N_nextWords(in, "where", 1);
        int col_index;
        noErr=((col_index=table.get_col_index(colToSearch))!=-1);

        if(noErr){
            string searchData=in-substr_SS(in, "", "where");
            if(oper=="between"){
                searchData=substr_SS(searchData, "between", "and");
            } else{
                searchData=substr_SS(searchData, oper,";");
            }
            removeSpaces_fromStart_andEnd(searchData);
            /*string searchData= substr_SS(in, colToSearch, ";");
            searchData=substr_from_c_to_c(searchData, 1, -1, '=', ' ');
            replace_chars(searchData, {' '}, -1);*/

            vector<int> foundRows;
            noErr=table.find_Rows_by_value(searchData, col_index, foundRows, oper, data2between);
            in-=(substr_SS(in, " where", ";", false, true) + ";");
            if(noErr){
                vector<string> updateData;
                while( !in.empty() ){
                    string tmp= substr_CC(in, 0, 1, ' ', ',');
                    tmp+=",";
                    if(tmp=="/err,"){
                        tmp= substr_CC(in, 0, -1);
                    }
                    in-=tmp;
                    if(tmp.find(',')){ tmp-=","; }
                    replace_chars(tmp, {' '}, -1);
                    updateData.push_back(tmp);


                }
                noErr= table.set_UPDATE_data(updateData, foundRows);

                if(noErr and !table.get_ForeignTables().empty()){ noErr=checkForeignKeys(table, foundRows[0]); }
            } /*else{
                cout << RED<<endl<<"No row containing"<<searchData<<"was found!" << RESET;
            }*/

        } else{
            cout << RED<<endl<<"No column "<<colToSearch<<" was found!"<<endl << RESET;
        }

    } else{
        cout << RED<<"Table named "<<tableName<<" doesn't exist!"<<endl << RESET;
    }

    if(!noErr){
        table=TableBackup;
    }else{
        updated_TablesNames.push_back(table.name);
    }
    return noErr;
}

bool Database::SELECT(string in) {
    bool noErr=true;
    string tableName = take_the_N_nextWords(in, "from", 1);
    noErr = !check_Table_existence(tableName, true);
    Table &table = Tables[find_Table(tableName)];
    string colToOrder="/err";
    vector <string> vec={"/err", "0", "/err"};
    int orden=0;
    if(noErr){
        vector <string> colNames;
        string tmp;
        bool exit=true;
        if(in.substr(0,in.find("from")).find('*')!=-1) colNames={"*"};
        else {
            do {
                tmp = substr_CC(in, 0, 1, ' ', ',');
                if (tmp == "/err") {
                    tmp = in.substr(0, in.find("from") - 1);
                    if (num_of_words(tmp) == 1) {
                        in -= (tmp + " ");
                        colNames.push_back(tmp);
                    } else {
                        exit = false;
                    }
                } else {
                    in -= (tmp + "," + " ");
                    colNames.push_back(tmp);
                }
            } while (exit);
        }
        if(in.find("order by")!=-1){
            if(in.find("asc")!=-1) orden = 1;
            else if(in.find("desc")!=-1) orden = -1;
            colToOrder = take_the_N_nextWords(in, "by", 1);
        }

        if(in.find('*')!=-1 and in.find("where")==-1){
            noErr=table.printCols({"*"}, vec, colToOrder, orden);
        }else if(in.find("where")!=-1){
            string oper = take_the_N_nextWords(in, "where", 2), data2="/err", data1="/err";
            if(oper=="between"){
                data1 = substr_SS(in, "between", "and");
                data2 = substr_SS(in, "and", "order");
                if(data2=="/err"){ data2 = substr_SS(in, "and", ";"); }
                removeSpaces_fromStart_andEnd(data2);
            } else{
                data1 = substr_SS(in, oper, "order");
                if(data1=="/err"){ data1 = substr_SS(in, oper, ";"); }
            }
            removeSpaces_fromStart_andEnd(data1);

            vec = {take_the_N_nextWords(in, "where", 1), oper, data1, data2};
            if(table.get_col_index(vec[0])!=-1){
                noErr=table.printCols(colNames, vec, colToOrder, orden);
            } else{
                noErr=false;
                cout << RED<<endl<<"No column "<<vec[0]<<" was found!"<<endl << RESET;
            }
        }else{
            noErr=table.printCols(colNames, vec, colToOrder, orden);
        }
    }
    cout<<endl;
    return noErr;
}

void Database::QUIT(){
    string path="../Database.txt";
    ofstream out;
    ifstream in;
    in.open(path);
    out.open(path, ios::trunc);
    for(Table & table:Tables){
        streampos tmp;
        table.printTable_to_file(out);
    }
    out.close();
}

bool Database::START() {
    bool noErr;
    ifstream in;
    in.open("../Database.txt", ios::in);
    if(!in){
        cout << RED<<endl<<"The file doesn't exist!"<<endl << RESET;
    }
    string line;
    int i=0;

    get_cleanLine(in, line);
    while(!in.eof()){
        this->Tables.resize(i+1);
        get_cleanLine(in, line);
        this->Tables[i].createTable_from_file(in, line);
        i++;
        get_cleanLine(in, line);

        /*streampos pos=in.tellg();
        get_cleanLine(in, line);
        if(line!="~"){ in.seekg(pos); }*/
    }
    return noErr;
}

bool Database::CREATE_TABLE(string in){
    bool noErr=true;
    string table_name= substr_CC(in, 0, 1);
    noErr=check_TableName(table_name);
    if(noErr and (noErr=check_Table_existence(table_name, false))){
        Table temp;//this creates a temporary Table

        string foreignKeys;
        if(in.find("foreign key")!=-1){
            foreignKeys = substr_SS(in, "foreign key", ");", false, true);
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

bool Database::setForeignKeys(string data, Table & thisTable) {
    bool noErr=true;
    string line = substr_CC(data, 0, 1, ' ', ',');
    while(noErr and !data.empty()) {
        line += ", ";
        if (line == "/err, ") {
            line = substr_CC(data, 0, -1);
        }
        data-=line;

        string thisTableElement= substr_CC(line, 1, 1, '(', ')');
        int thisCol_i= thisTable.get_col_index(thisTableElement);
        if(thisCol_i != -1){
            string foreignTableName = substr_CC(line, 4, 5);
            int foreignTable_i = find_Table(foreignTableName);

            if (foreignTable_i != -1){
                Table & foreignTable=Tables[foreignTable_i];

                string foreignTableElement= substr_CC(line, 2, 2, '(', ')');
                int foreignCol_i= foreignTable.get_col_index(foreignTableElement);

                if(foreignCol_i != -1){
                    vector<int> tmp_ForeignTables=thisTable.get_ForeignTables();
                    vector<int> tmp_ConnectedCols=thisTable.get_ConnectedCols();
                    vector<int> tmp_ForeignCols=thisTable.get_ForeignCols();

                    tmp_ForeignTables.push_back(foreignTable_i);
                    tmp_ConnectedCols.push_back(thisCol_i);
                    tmp_ForeignCols.push_back(foreignCol_i);

                    thisTable.set_ForeignTables(tmp_ForeignTables);
                    thisTable.set_ConnectedCols(tmp_ConnectedCols);
                    thisTable.set_ForeignCols(tmp_ForeignCols);

                    line = substr_CC(data, 0, 1, ' ', ',');
                    foreignTable.set_Foreign_linked(true);
                } else{
                    cout << RED<<endl<<"Uncaught reference to a non existence Column in" << RESET;
                    cout << RED<<" the foreign Table "<<foreignTableName << RESET;
                    cout << RED<<"! (Column name: " << foreignTableElement<< ")"<<endl << RESET;
                }
            }else {
                cout << RED << endl << "Uncaught reference to a non existence Table! (Table name: " << foreignTableName << ")"<<endl << RESET;
                noErr=false;
            }
        } else{
            cout << RED << "No element called " << thisTableElement << " exists in this Table!"<<endl << RESET;
            noErr=false;
        }
    }
    return noErr;
}

bool Database::readCommands_from_file(const string &filepath, bool &quit) {
    bool noErr=true;
    quit=false;

    ifstream in;
    in.open(filepath, ios::in);
    if(!in){
        cout << RED<<endl<<"The file "<< filepath <<" doesn't exist!"<<endl << RESET;
        noErr=false;
    }

    if(noErr){
        string line="the cake is a lie", command;
        int line_i=1, startLine_i=1, endLine_i=1;
        bool start=true;
        while(line!="~" and noErr and !quit) {
            command="";
            do{
                if(start){ startLine_i=line_i; start=false;}
                get_cleanLine(in, line);
                if(line!="~"){
                    while(line=="\r" or removeSpaces_fromStart_andEnd(line)[0]=='#'){
                        get_cleanLine(in, line);
                        line_i++;
                        startLine_i++;
                    }
                    if(line!="~"){
                        replace_chars(line, {'\r'}, -1);
                        line-="#"+substr_CC(line, 1, -1, '#');
                        command += " " + line;
                        line_i++;
                    }
                }
            } while (line.find(';') == -1 and line!="~");

            if(line!="~"){
                endLine_i = line_i - 1;
                start = true;

                noErr = process_command(command, quit);
                if (!noErr) {
                    if (endLine_i == startLine_i) {
                        cout << RED << endl << "Error at line " << startLine_i<<endl << RESET;
                    } else {
                        cout << RED << endl << "Error from line " << startLine_i
                             << " to line " << endLine_i << "!"<<endl << RESET;
                    }
                }
                if(quit){
                    cout<<endl<<"QUIT command has been executed"<<endl<<"Goodbye!"<<endl;
                }
            }
        }
    }
    return noErr;
}

