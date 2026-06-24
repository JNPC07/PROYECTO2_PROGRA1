#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //No usamos pero fue añadida por si acaso
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <cmath> //No usamos pero fue añadida por si acaso
#include "CTurtle.hpp"
#include <fstream>
#include <sstream>
//Definicion de librerias para que ciertas funciones puedan existir.
using namespace std;
using namespace cturtle;
//Uso de la palabra clave "void" para establecer un menú que no devuelva ningún valor. (cris)
void menu(){
    int opcionMenu;
    cout << " " << endl;
    cout << "--- BIENVENIDO AL JUEGO DEL AHORCADO ---" << endl;
    cout << "--- SELECCION DE JUEGO ---" << endl;
    cout << "[1] Un Jugador" << endl;
    cout << "[2] Dos Jugadores" << endl;
    cout << "[3] Creditos" << endl;
    cout << "Opcion: ";
}
//De igual manera, se usa "void" para comenzar a plantear instrucciones del dibujo (cris)
void dibujarAhorcado(Turtle& t, int intentos) {
    t.pencolor({255, 255, 255});
    t.width(3);
    t.speed(TS_FASTEST);
    
    // EL POSTE QUE SIEMPRE TIENE QUE ESTAR AHI :D
    
    t.penup(); t.goTo(-100, -150); t.pendown();
    t.goTo(0, -150);          
    t.goTo(-50, -150); t.goTo(-50, 150); 
    t.goTo(50, 150);          
    t.goTo(50, 110); // 

  	// CABEZA :D
    if (intentos <= 5) {
        t.penup(); t.goTo(65, 95); t.setheading(90); t.pendown();
        t.circle(15); 
    }
    // TORSO :D
    if (intentos <= 4) {
        t.penup(); t.goTo(50, 80); t.pendown();
        t.goTo(50, 10);
    }
    // BRAZO 1
    if (intentos <= 3) {
        t.penup(); t.goTo(50, 65); t.pendown();
        t.goTo(25, 45);
    }
    // BRAZO 2
    if (intentos <= 2) {
        t.penup(); t.goTo(50, 65); t.pendown();
        t.goTo(75, 45);
    }
    // PIERNA 1
    if (intentos <= 1) {
        t.penup(); t.goTo(50, 10); t.pendown();
        t.goTo(25, -40);
    }
    //PIERNA 2
    if (intentos <= 0) {
        t.penup(); t.goTo(50, 10); t.pendown();
        t.goTo(75, -40);
    }
}
//Inicio del programa, se definen variables e instrucciones para que se devuelva lo solicitado en Cturtle. (cris)

void Mayusculas(string &mayus){
    for (int i = 0; i < mayus.length(); i++) {
        mayus[i] = toupper(mayus[i]);
    }
}

void VerificarAcertado(string palabra, char letra, string &palabraAdivinada, bool &acertado){
    for (int i = 0; i < palabra.length(); i++) {
        if (palabra[i] == letra) {
            palabraAdivinada[i] = letra;
            acertado = true;
        }
    }
}

void ValidacionEsPalabra(string &palabra){
    bool entradaPalabraValida = true;
    while (entradaPalabraValida) {
        cin >> palabra;
        /*Filtra si contiene caracteres numéricos*/
        bool noEsPalabra = false;
        for (int i = 0; i < palabra.length(); i++) {
            if (!isalpha(palabra[i])) {
                noEsPalabra = true;
                break;
            }
        }

        if (noEsPalabra) {
            cout << "Por Favor, ingrese una palabra: ";
            continue; // Regresa al inicio del while para pedir otra palabra
        } else if (!noEsPalabra){
            /*Hacer mayúsculas*/
            Mayusculas(palabra);
            /*Si todo está en orden, salimos del bucle de validacion
            de entrada de la palabra a Adivinar*/
            entradaPalabraValida = false;
        } /*Llave del condicional noEsPalabra*/
    } /*llave del while entradPalabraValida*/
}

void ValidacionOpcionMenu(int &opcionMenuInt){
    bool opcionValida = false;
    string opcionMenuValidacion;
    while (!opcionValida) {
        cin >> opcionMenuValidacion;
        /*Filtra si contiene caracteres no numéricos*/
        bool NotieneNumero = false;
        for (int i = 0; i < opcionMenuValidacion.length(); i++) {
            if (!isdigit(opcionMenuValidacion[i])) {
                NotieneNumero = true;
                break;
            }
        }

        if (NotieneNumero) {
            cout << "ERROR - NO EXISTE ESA OPCION: ";
            continue; // Regresa al inicio del while para pedir otra opcion del menu
        } else {
            opcionMenuInt = stoi(opcionMenuValidacion);
            opcionValida = true; // Todo en orden, salimos del bucle de validación
        }

    }
}

void ValidacionAlfa(string caracterespecial, char &letra){
    char mayuscula;
    while ((caracterespecial.find(letra) != string::npos) || (isdigit(letra))){
            cout << "Por favor, intenta ingresar una letra o la palabra completa: ";
            cin >> letra; 
            mayuscula = toupper(letra);
            letra = mayuscula;
        /*AQUI BORRAMOS TODO RESIDUO PARA LA SIGUIENTE LECTURA*/
            cin.ignore(100, '\n');
        }
}
typedef struct {
    string usuario;
    string contrasena; 
} tInformacion;
bool existeUsuario(string buscarUsuario, string buscarContrasena) {
    string path = "usuarios.txt";
    ifstream file(path); 

    string linea; 
    while(getline(file, linea)) {
        stringstream ss(linea);

        string nombre;
        string contrasena;

        getline(ss,nombre,',');
        getline(ss,contrasena,',');

        if (nombre == buscarUsuario && contrasena == buscarContrasena) {
            file.close();
            return true;
        }
    }

    file.close();
    return false; 
}
void agregarUsuario() {
    tInformacion nuevo;

    cout << "Ingrese el nombre para su usuario: ";
    cin >> nuevo.usuario;

    cout << "Ingrese una contrasenia: ";
    cin >> nuevo.contrasena;

    ofstream file("usuarios.txt", ios::app);

    file << endl << nuevo.usuario << "," << nuevo.contrasena << endl;
    file.close();

    cout << "Usuario creado correctamente \n";
}
bool iniciarSesion() {
    bool resultado; 
    string nombre;
    string contrasena;

    cout << "Ingrese el nombre de su usuario: ";
    cin >> nombre;
    
    cout << "Ingrese su contrasenia: ";
    cin >> contrasena; 

    if(!existeUsuario(nombre, contrasena)) {
        cout << "Usuario y contrasenia no encomtrado \n";

        string op;
        cout << "¿Desea registrar su usuario? Marque [Y/N]: ";
        cin >> op;
        Mayusculas(op);

        if (op == "Y") {
            agregarUsuario();
        }
        resultado = false;
    }
    if (existeUsuario(nombre, contrasena)) {
        cout << "Se ha iniciado sesion de manera exitosa. Bienvenid@ " << nombre << endl;
        resultado = true;
    }

    return resultado; 
}
int main() {

    bool acceso = iniciarSesion();

    string path = "palabrasAdivinar.txt";
    ifstream file;
    string palabrasTabla;
    file.open(path, ios::in);
    vector<string> dataPalabraSecreta;

    while (getline(file, palabrasTabla)) {
        stringstream ss(palabrasTabla);
        while (getline(ss, palabrasTabla, ',')) {
        dataPalabraSecreta.push_back(palabrasTabla);
        }
    }


    string opcionMenuValidacion;
    int opcionMenuInt;
    TurtleScreen screen;
    screen.bgcolor({30, 30, 30});
    Turtle t(screen);
    t.hideturtle();
    //Se define un vector (lista) que devuelva palabras. (cris)
    /*vector<string> palabraSecreta = {
        "PROGRAMACION",
        "PROFEPONGAMEDIEZ", 
        "LOGARITMO", 
        "MEGUSTAPROGRAMAR", 
        "POLITECNICA", 
        "GRADUACION", 
        "INGENIERIA", 
        "COMPUTADORA", 
        "ECUADOR", 
        "VISUAL", 
        "LINUX" ,
        "MEMORIA",
        "CALENDARIO",
        "REDESNEURONALES",
        "COTOPAXI",
        "MUNDIAL", 
        "SOPORTE",
        "PRACTICA",
        "FUTURO",
        "ACTUALIZACION",
        "MULTITAREAS",
        "TECNOLOGIA",
        "INTELIGENCIA",
        "ALMACENAMIENTO"
    };*/
    
    



    srand(time(0));
    int puntaje = 0; //Inicializar un contador (c)
    char jugadores;  //Guardar el caracter jugadores(c)
    const string caracterEspeciales = "+!#$%&/()=?¡°|||¨*[]ñ_:.-{},;<'>\"\'\\"; //delimitación de caracteres especiales (c)
    bool acertado; //Indicara si la respuesta es correcta (c)
    bool seguirjugando = true; //Se ejecuta siempre que se cumpla la condicion(c)


    do {  //El menu se ejecutara al menos una vez, luego dependera de que condicion cumple (c)
        menu(); //muestra opciones para que el usuario decida (c)
        bool opcionValida = false;
        ValidacionOpcionMenu(opcionMenuInt);

        switch (opcionMenuInt) { //Inicio de evaluacion de la opcion seleccionada. (c)
/*CASO 1 | UN JUGADOR*/
            case 1:{
                system("cls");  
                bool seguirjugando = true;
                cout << "===========================================================" << endl; // Impreso por la estetica del juego (c)
                cout << "PARA ESTE MODO ADIVINA LA MAYOR CANTIDAD DE PALABRAS POSIBLE" << endl; //Instruccion (c)
                while (seguirjugando){ //Inicio del bucle mientras se seleccione "seguir jugando"
                    
                    t.reset(); //Reinicio de la tortuga (c)
                    int posicion = rand() % dataPalabraSecreta.size(); //Genera una palabra aletoria, de acuerdo a la lista previamente hecha (c)
                    string palabra = dataPalabraSecreta[posicion]; //Guarda la palabra aletoria (C)
                    string palabraAdivinada(palabra.length(), '_'); //Hace que la palabra seleccionada se oculte estableciendo "_" por cada letra(c)
                    /*Este cout solo es para probar el funcionamiento del programa
                    se lo debe de borrar para jugar sin ver la palabra a adivinar*/
                    cout << palabra << endl;
                    int intentosRestantes = 6;
                    char mayuscula;
                    
                    //Se declara otro valor de verdad para validar que el jugador gane o pierda al instante.
                    bool muerteInstantanea=false;

                
                    string entrada;
                    dibujarAhorcado(t, intentosRestantes);
                        /*Bucle de la PALABRA ACTUAL, este apartado se ha conservado
                        de la mejor manera posible desde la primera version del codigo del juego*/
                            while (intentosRestantes > 0 && palabraAdivinada != palabra) {
                            cout << "\nPalabra: " << palabraAdivinada << endl;
                            cout << "Intentos restantes: " << intentosRestantes << endl;
                            cout << "Introduce una letra o palabra: ";
                            cin >> entrada;
                            
                        
                            
                            Mayusculas(entrada);

                            
                        bool entradaValida= true;
                        for (int i=0; i<entrada.length(); i++)
                        {
                        if (!isalpha(entrada[i]))
                        {
                        entradaValida=false;
                        break;    
                        }    
                        }
                        if (!entradaValida){
                            cout<<"Recuerde ingresar solo letras, los simbolos y numeros no son validos. "<<endl;
                            continue;
                        }

                        if (entrada.length() > 1) {
                            if (entrada == palabra) {
                                palabraAdivinada = palabra;
                                break;
                            } else {
                                cout << "¡Palabra incorrecta! Muerte instantanea." << endl;
                                muerteInstantanea = true;
                                intentosRestantes = 0;
                                dibujarAhorcado(t, 0);
                                break;
                            }
                        }
                        if (muerteInstantanea) {break;
                        }
                        /*Aqui debemos convertir el string en cadena de caracteres en caso que el jugador
                            no haya adivinado la palabra completa todavía y quiera seguir poniendo letras,
                            para ello definimos la variable letra como char, y el string entrada se 
                            separa en caracteres*/
                        else
                        {
                            char letra = entrada[0];

                            ValidacionAlfa(caracterEspeciales, letra);

                                acertado = false;
                                VerificarAcertado(palabra,letra,palabraAdivinada,acertado);

                                /*Esta es la condicional que evalua si el bucle for encontró o no una igualdad 
                                en el recorrido de la palabra.*/
                                if (!acertado) {
                                    intentosRestantes--;
                                    cout << "¡Incorrecto! Perdiste una vida." << endl;
                                } else {
                                    cout << "¡Bien hecho! Acertaste una letra." << endl;
                                }
                                dibujarAhorcado(t, intentosRestantes);
                                }/*Llave del else de muerte instantanea*/
                        } /*Llave del while del desglose de la palabra y validacion de igualdades*/
                        //Verificacion para saber si adivina o no
                        if (palabraAdivinada == palabra) {
                            cout << "\n--- ¡FELICIDADES, ADIVINASTE! ---" << endl;
                            cout << "La palabra era: " << palabra << endl;
                            //Vamos diciéndole el puntaje que lleva en racha
                            puntaje = puntaje + 100;
                            cout << "Hasta ahora llevas: " << puntaje << " puntos" << endl;
                            /*Elimina caracteres residuales de la palabra anterior ya adivinada
                            se le pidio que borre los siguientes 100 caracteres hasta hallar un Enter*/
                            cin.ignore(100, '\n');
                        //Si no adivina entonces termina todo el juego y le damos puntaje total
                        } else if (palabraAdivinada != palabra){
                            cout << "\n--- GAME OVER ---"<< endl; 
                            cout << "Te has quedado sin intentos." << endl; 
                            cout << "La palabra era: " << palabra << endl;
                            cout << "Tu puntaje total fue de: " << puntaje << endl;
                            /*Estos son rangos que optiene el usuario dependiendo
                            del puntaje, condicionales anidadas dentro del else if si pierde.*/
                                if (puntaje >= 1000){
                                    cout << "Estas en el top 1" << endl;
                                } else if (puntaje >= 500){
                                    cout << "Estas dentro del top 10" << endl;
                                } else if (puntaje >= 100){
                                    cout << "Estas dentro del top 20" << endl;
                                } else {
                                    cout << "Suerte para la proxima" << endl;
                                } 
                            char seleccionOpcion, mayusSeleccion;
                            cout << "--- JUGAR DE NUEVO ---" << endl;
                            cout << "[Y/N]: "; 
                            cin >> seleccionOpcion;
                            mayusSeleccion = toupper(seleccionOpcion);
                            seleccionOpcion = mayusSeleccion;
                            /*RESETEO DEL PUNTAJE*/
                            puntaje = 0;
                            while ((seleccionOpcion != 'Y') && (seleccionOpcion != 'N')){
                                cout << "Opcion invalida, intente de nuevo: " << endl;
                                cout << "--- JUGAR DE NUEVO ---" << endl;
                                cout << "[Y/N]: "; 
                                cin >> seleccionOpcion;
                                mayusSeleccion = toupper(seleccionOpcion);
                                seleccionOpcion = mayusSeleccion;  
                                } /*Llave del while(seleccion)*/
                            if (seleccionOpcion == 'Y'){
                                seguirjugando = true;
                            } else if (seleccionOpcion == 'N'){
                                seguirjugando = false;
                                system("cls");
                                cout << "--- GRACIAS POR JUGAR ---" << endl;
                                cout << "--- CREDITOS FINALES ---" << endl;
                                cout << "- William Chuquimarca" << endl;
                                cout << "- Cristina Granda" << endl;
                                cout << "- Jael Pacheco" << endl;
                                cout << "- Sergio Betancourt" << endl;
                            } 
                        } /*Llave condicional else if palabraAdivinada != palabra*/


                }   /*llave del while(seguirjugando)*/
                
                
            }


/*CASO 2 | DOS JUGADORES*/ 
                break;
            case 2:{
                /*Muy similar al modo 1 jugador, contamos con un bucle principal (seguirjugando) para permitir
                a los jugadores jugar nuevamente hasta que decidan que ya no quieren, de ahí, el bucle principal finaliza.
                Tenemos dos bucles más añadidos dentro del principal, tenemos el bucle de validacion de rondas, no puede meter
                algo que no sea un número par y positivo, añadimos un Bucle Interno de Rondas, este contiene el bucle de la palabra
                a adivinar, es decir, su desglose y validacion de igualdades, victoria y derrota. Este bucle fue añadido para que se vuelva a pedir 
                otra palabra la cual el otro amigo adivinará y se repetirá dependiendo del numero de rondas ingresados por los jugadores, 
                se iteran el numero de rondas que se estan jugando hasta que sea igual al ingresado, solo ahí termina el bucle interno de rondas 
                y pasamos a la validacion de volver a jugar o no, esta validacion está dentro del bucle principal (seguirjugando)*/
                bool seguirjugando = true;
                while (seguirjugando){
                    system("cls");
                    cout << "===========================================================" << endl;
                    cout << "PARA ESTE MODO DECIDAN ENTRE USTEDES: Jugador Uno | Jugador Dos" << endl;
                    cout << "ESCOJAN EL NUMERO PAR DE RONDAS A JUGAR: ";
                    string entradaUser;
                    int limiteTurno = 0;
                    bool entradaValida = false;
                    t.reset();
                    while (!entradaValida) {
                        cin >> entradaUser;
                        /*Filtra si contiene caracteres no numéricos
                        Hicimos que la entrada de Rondas entradaUser sea un string para luego con un for
                        ir viendo cada caracter del string (por iteraciones dependiendo del tamaño del string), 
                        como un decimal tiene un punto, el punto no es un numero entonces tieneDecimales es verdadero 
                        y le pediremos que ingrese un numero positivo y par, si se detecta algo que sea distinto 
                        a un numero incluyendo caracteres especiales se le pedirá que ingrese un numero, es la solucion más simple que pudimos hallar.*/
                        bool tieneDecimales = false;
                        for (int i = 0; i < entradaUser.length(); i++) {
                            if (!isdigit(entradaUser[i])) {
                                tieneDecimales = true;
                                break;
                            }
                        }

                        if (tieneDecimales) {
                            cout << "Por Favor, ingrese un numero de rondas positivo y par: ";
                            continue; // Regresa al inicio del while para pedir otra entrada
                        }

                        /*Pasamos de string a un integer para evaluar el 1 y 2*/
                        limiteTurno = stoi(entradaUser);

                        if ((limiteTurno <= 0) || (limiteTurno%2 != 0)) {
                            cout << "Por Favor, ingrese un numero de rondas positivo y par: ";
                        } else {
                            entradaValida = true; // Todo en orden, salimos del bucle de validación
                        }
                    } /*Llave del While entradaValida*/ 

                    int turnoJugadores = 0;
                    int puntajePlayer1 = 0;
                    int puntajePlayer2 = 0;
                    bool BucleInternoRondas = true;
                    
                    while (BucleInternoRondas){
                        string palabra, palabraAdivinada, entrada;
                        char letra, mayuscula;
                        int intentosRestantes = 6;
                        bool acertado;

                        //Ingresar la palabra
                        cout <<"INGRESE UNA PALABRA, EL OTRO TIENE QUE ADIVINAR: "; 

                        ValidacionEsPalabra(palabra);
            
                        
                        //Borrar la palabra de la pantalla
                        system("cls");

                        palabraAdivinada = string(palabra.length(), '_');

                        //Inicio del juego
                        cout <<"- ADIVINA LA PALABRA DE TU AMIGO! -" <<endl;
                        t.reset();
                        
                        bool muerteInstantanea=false;
                        dibujarAhorcado(t, intentosRestantes);
                        
                                while (intentosRestantes > 0 && palabraAdivinada != palabra) {
                                cout << "\nPalabra: " << palabraAdivinada << endl;
                                cout << "Intentos restantes: " << intentosRestantes << endl;
                                cout << "Introduce una letra o palabra: ";
                                cin >> entrada;
                                
                    
                                
                                Mayusculas(entrada);

                                
                            bool entradaValida= true;
                            for (int i=0; i<entrada.length(); i++)
                            {
                            if (!isalpha(entrada[i]))
                            {
                            entradaValida=false;
                            break;    
                            }    
                            }
                            if (!entradaValida){
                                cout<<"Recuerde ingresar solo letras, los simbolos y numeros no son validos. "<<endl;
                                continue;
                            }

                            if (entrada.length() > 1) {
                                if (entrada == palabra) {
                                    palabraAdivinada = palabra;
                                    break;
                                } else {
                                    cout << "¡Palabra incorrecta! Muerte instantanea." << endl;
                                    muerteInstantanea = true;
                                    intentosRestantes = 0;
                                    dibujarAhorcado(t, 0);
                                    break;
                                }
                            }
                            if (muerteInstantanea) {break;
                            }
                            
                            else
                        
                            {
                                char letra = entrada[0];

                            
                                    while ((caracterEspeciales.find(letra) != string::npos) || (isdigit(letra))){
                                        cout << "Por favor, intenta ingresar una letra o la palabra completa: ";
                                        cin >> letra; 
                                        mayuscula = toupper(letra);
                                        letra = mayuscula;
                                        cin.ignore(100, '\n');
                                    }
                                    acertado = false;

                                    VerificarAcertado(palabra, letra, palabraAdivinada, acertado);
                                    
                                    if (!acertado) {
                                        intentosRestantes--;
                                        cout << "¡Incorrecto! Perdiste una vida." << endl;
                                        dibujarAhorcado(t, intentosRestantes);
                                    } else {
                                        cout << "¡Bien hecho! Acertaste una letra." << endl;
                                    }

                                    }
                            }
                            if (palabraAdivinada == palabra) {
                                cout << "\n--- ¡FELICIDADES, ADIVINASTE! ---" << endl;
                                cout << "La palabra era: " << palabra << endl;
                                cout << "- PUNTAJES ACTUALES -" << endl;
                                if (turnoJugadores%2 == 0){
                                    puntajePlayer1 = puntajePlayer1 + 1;
                                } else if (turnoJugadores%2 != 0){
                                    puntajePlayer2 = puntajePlayer2 + 1;
                                }
                                cout << "Jugador Uno: " << puntajePlayer1 << endl;
                                cout << "Jugador Dos: " << puntajePlayer2 << endl;
                                turnoJugadores++;
                                cin.ignore(100, '\n');
                            //Si no adivina entonces termina todo el juego y le damos puntaje total
                            } else if (palabraAdivinada != palabra){
                                cout << "\n--- NO ADIVINASTE---"<< endl;  
                                cout << "La palabra era: " << palabra << endl;
                                cout << "- PUNTAJES ACTUALES -" << endl;
                                if (turnoJugadores%2 == 0){
                                    puntajePlayer1 = puntajePlayer1 + 0;
                                } else if (turnoJugadores%2 != 0){
                                    puntajePlayer2 = puntajePlayer2 + 0;
                                }
                                cout << "Jugador Uno: " << puntajePlayer1 << endl;
                                cout << "Jugador Dos: " << puntajePlayer2 << endl;
                                turnoJugadores++;
                                cin.ignore(100, '\n');
                                    
                                    
                        
                            }
                        /*bucle false seguir jugando si*/
                        if (turnoJugadores == limiteTurno){
                            BucleInternoRondas = false;
                            cout << "--- PUNTAJES ---" << endl;
                            cout << "Jugador Uno: " << puntajePlayer1 << endl;
                            cout << "Jugador Dos: " << puntajePlayer2 << endl;
                            if (puntajePlayer1 > puntajePlayer2){
                                cout << "Jugador Uno es el GANADOR" << endl;
                            } else if (puntajePlayer1 < puntajePlayer2) {
                                cout << "Jugador Dos es el GANADOR" << endl;
                            } else if (puntajePlayer1 == puntajePlayer2){
                                cout << "EMPATE" << endl;
                            }
                        }

                    } /*Llave Bucle Interno de Rondas*/
                    
                    char seleccionOpcion, mayusSeleccion;
                    cout << "--- JUGAR DE NUEVO ---" << endl;
                    cout << "[Y/N]: "; 
                    cin >> seleccionOpcion;
                    mayusSeleccion = toupper(seleccionOpcion);
                    seleccionOpcion = mayusSeleccion;
                    /*RESETEO DEL PUNTAJE*/
                    puntaje = 0;
                    while ((seleccionOpcion != 'Y') && (seleccionOpcion != 'N')){
                        cout << "Opcion invalida, intente de nuevo: " << endl;
                        cout << "--- JUGAR DE NUEVO ---" << endl;
                        cout << "[Y/N]: "; 
                        cin >> seleccionOpcion;
                        mayusSeleccion = toupper(seleccionOpcion);
                        seleccionOpcion = mayusSeleccion;  
                        } /*Llave del while(seleccion)*/
                    if (seleccionOpcion == 'Y'){
                        seguirjugando = true;
                    } else if (seleccionOpcion == 'N'){
                        seguirjugando = false;
                    }

                } /*Llave while (seguirjugando)*/    
                
            } /*Llave cierre case 2*/
                
            
                break;
            case 3:{
                system("cls");
                cout << "--- GRACIAS POR JUGAR ---" << endl;
                cout << "--- CREDITOS FINALES ---" << endl;
                cout << "- William Chuquimarca" << endl;
                cout << "- Cristina Granda" << endl;
                cout << "- Jael Pacheco" << endl;
                cout << "- Sergio Betancourt" << endl;

            }
                

                break;
            default:
                cout << "ERROR - NO EXISTE ESA OPCION: " << endl;
        }
    } while (opcionMenuInt != 3);

    system("pause");
    return 0;
}