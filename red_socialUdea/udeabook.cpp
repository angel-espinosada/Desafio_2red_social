#include "udeabook.h"
#include "memoria.h"
#include "foto.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>.


udeabook::udeabook()
{
    matriz = nullptr;      // todavia no hay matriz
    n = 0;
    actual = -1;           // nadie ha iniciado sesion
}

udeabook::~udeabook()
{
    delete[] matriz;       // devolver la matriz al terminar
}



bool udeabook::cargar_usuarios(string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "No se pudo abrir " << nombre_archivo << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        memoria::contar();
        if (linea.empty()) continue;

        stringstream ss(linea);
        string nombre, nac, correo, clave, ciudad, pais, insc;
        getline(ss, nombre, ';');
        getline(ss, nac,    ';');
        getline(ss, correo, ';');
        getline(ss, clave,  ';');
        getline(ss, ciudad, ';');
        getline(ss, pais,   ';');
        getline(ss, insc,   ';');

        usuario u(nombre, stoi(nac), correo, clave, ciudad, pais, stoi(insc));
        usuarios.agregar(u);
    }
    archivo.close();
    return true;
}

bool udeabook::cargar_amistades(string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "No se pudo abrir " << nombre_archivo << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        memoria::contar();
        if (linea.empty()) continue;

        stringstream ss(linea);
        string sa, sb;
        getline(ss, sa, ';');
        getline(ss, sb, ';');
        int a = stoi(sa);
        int b = stoi(sb);
        if (a < 0 || a >= n || b < 0 || b >= n) {
            cout << "Amistad invalida: " << linea << endl;
            continue;
        }

        matriz[a * n + b] = true;
        matriz[b * n + a] = true;
        usuarios[a].agregar_amigo(b);
        usuarios[b].agregar_amigo(a);
    }
    archivo.close();
    return true;
}

bool udeabook::cargar_solicitudes(string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "No se pudo abrir " << nombre_archivo << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        memoria::contar();
        if (linea.empty()) continue;

        stringstream ss(linea);
        string se, sr;
        getline(ss, se, ';');
        getline(ss, sr, ';');
        int emisor = stoi(se);
        int receptor = stoi(sr);
        if (emisor < 0 || emisor >= n || receptor < 0 || receptor >= n) continue;

        usuarios[receptor].agregar_solicitud(emisor);   // la recibe el receptor
    }
    archivo.close();
    return true;
}

bool udeabook::cargar_datos()
{
    if (!cargar_usuarios("usuarios.txt"))
        return false;

    n = usuarios.gettamano();
    matriz = new bool[n * n];
    for (int i = 0; i < n * n; i++)
        matriz[i] = false;

    if (!cargar_amistades("amistades.txt"))
        return false;
    if (!cargar_solicitudes("solicitudes.txt"))
        return false;
    if (!cargar_mensajes("mensajes.txt"))
        return false;
    if (!cargar_albumes("albumes.txt"))
        return false;
    if (!cargar_fotos("fotos.txt"))
        return false;

    cout << "Usuarios cargados: " << n << endl;
    return true;
}



bool udeabook::login()
{
    string nombre, clave;
    cout << "===== Iniciar sesion =====" << endl;
    cout << "Usuario: ";
    cin >> nombre;
    cout << "Clave: ";
    cin >> clave;

    int i = buscar_usuario(nombre);
    if (i == -1 || usuarios[i].getclave() != clave) {
        cout << "Usuario o clave incorrectos" << endl;
        return false;
    }
    actual = i;
    cout << "Bienvenido, " << nombre << endl;
    return true;
}

//Mejora con busqueda binaria
int udeabook::buscar_usuario(string nombre)
{
    int ini = 0, fin = n - 1;
    while (ini <= fin) {
        memoria::contar();
        int medio = (ini + fin) / 2;
        string nom = usuarios[medio].getnombre_usuario();
        if (nom == nombre) return medio;
        if (nombre < nom) fin = medio - 1;
        else              ini = medio + 1;
    }
    return -1;
}

int udeabook::amigos_en_comun(int yo, int otro)
{
    ArregloDinamico<int>& mis_amigos = usuarios[yo].getamigos();
    int comun = 0;
    for (int k = 0; k < mis_amigos.gettamano(); k++) {
        memoria::contar();
        if (matriz[otro * n + mis_amigos[k]])
            comun++;
    }
    return comun;
}

void udeabook::sortear3(int* boletas)
{
    ArregloDinamico<int>& amigos = usuarios[actual].getamigos();
    for (int vez = 0; vez < 3; vez++) {
        int total = 0;
        for (int i = 0; i < amigos.gettamano(); i++) {
            memoria::contar();
            total += boletas[i];
        }
        if (total == 0) break;

        int r = rand() % total;
        int acumulado = 0;
        int ganador = 0;
        for (int i = 0; i < amigos.gettamano(); i++) {
            memoria::contar();
            acumulado += boletas[i];
            if (acumulado > r) { ganador = i; break; }
        }

        string nombre = usuarios[amigos[ganador]].getnombre_usuario();
        cout << "  - " << nombre << ": /users/udeabook/" << nombre << "/albums/profile.png" << endl;
        boletas[ganador] = 0;
    }
}

void udeabook::mostrar_mejores_amigos()
{
    ArregloDinamico<int>& amigos = usuarios[actual].getamigos();
    int m = amigos.gettamano();
    cout << "Tienes " << m << " amigos" << endl;
    if (m == 0) return;

    int* boletas = new int[m];
    for (int i = 0; i < m; i++) {
        memoria::contar();
        int comun = amigos_en_comun(actual, amigos[i]);
        if (comun <= 10)      boletas[i] = 2;
        else if (comun <= 20) boletas[i] = 5;
        else                  boletas[i] = 7;
    }

    cout << "\nTus mejores amigos:" << endl;
    sortear3(boletas);

    char resp;
    cout << "Actualizar fotos? (s/n): ";
    cin >> resp;
    if (resp == 's' || resp == 'S') {
        cout << "Otros amigos:" << endl;
        sortear3(boletas);
    }
    delete[] boletas;
}




bool udeabook::tiene_solicitud(int de, int para)
{
    ArregloDinamico<int>& sol = usuarios[para].getsolicitudes();
    for (int i = 0; i < sol.gettamano(); i++) {
        memoria::contar();
        if (sol[i] == de) return true;
    }
    return false;
}

void udeabook::enviar_solicitud_a(int destino)
{
    if (destino == actual) {
        cout << "No puedes enviarte una solicitud a ti mismo" << endl;
    } else if (matriz[actual * n + destino]) {
        cout << "Ya son amigos" << endl;
    } else if (tiene_solicitud(actual, destino)) {
        cout << "Ya le enviaste una solicitud" << endl;
    } else if (tiene_solicitud(destino, actual)) {
        cout << "Esa persona ya te envio una solicitud: aceptala" << endl;
    } else {
        usuarios[destino].agregar_solicitud(actual);
        cout << "Solicitud enviada a " << usuarios[destino].getnombre_usuario() << endl;
    }
}

void udeabook::enviar_solicitud()
{
    string nombre;
    cout << "Nombre del usuario: ";
    cin >> nombre;
    int destino = buscar_usuario(nombre);
    if (destino == -1) {
        cout << "No existe ese usuario" << endl;
        return;
    }
    enviar_solicitud_a(destino);
}

void udeabook::aceptar_solicitud()
{
    ArregloDinamico<int>& sol = usuarios[actual].getsolicitudes();
    if (sol.gettamano() == 0) {
        cout << "No tienes solicitudes" << endl;
        return;
    }

    cout << "Solicitudes recibidas:" << endl;
    for (int i = 0; i < sol.gettamano(); i++) {
        memoria::contar();
        cout << "  " << i + 1 << ". " << usuarios[sol[i]].getnombre_usuario() << endl;
    }
    int op;
    cout << "Numero a aceptar (0 = ninguna): ";
    cin >> op;
    if (op < 1 || op > sol.gettamano()) return;

    int e = sol[op - 1];
    matriz[actual * n + e] = true;          // ahora son amigos, en los dos sentidos
    matriz[e * n + actual] = true;
    usuarios[actual].agregar_amigo(e);
    usuarios[e].agregar_amigo(actual);
    sol.eliminar(op - 1);                    // ya no es una solicitud pendiente
    cout << "Ahora eres amigo de " << usuarios[e].getnombre_usuario() << endl;
}


void udeabook::ver_sugerencias()
{
    int k;
    cout << "Cuantas sugerencias (1 a 20): ";
    cin >> k;
    if (k < 1 || k > 20) {
        cout << "Debe ser un numero entre 1 y 20" << endl;
        return;
    }

    int* comun = new int[n];
    for (int i = 0; i < n; i++)
        comun[i] = 0;

    ArregloDinamico<int>& mis_amigos = usuarios[actual].getamigos();
    for (int i = 0; i < mis_amigos.gettamano(); i++) {
        ArregloDinamico<int>& de_el = usuarios[mis_amigos[i]].getamigos();
        for (int j = 0; j < de_el.gettamano(); j++) {
            memoria::contar();
            int b = de_el[j];
            if (b != actual && !matriz[actual * n + b])
                comun[b]++;
        }
    }


    int* elegidos = new int[k];
    int cuantos = 0;
    cout << "Sugerencias:" << endl;
    for (int vez = 0; vez < k; vez++) {
        int mejor = -1;
        for (int i = 0; i < n; i++) {
            memoria::contar();
            if (comun[i] > 0 && (mejor == -1 || comun[i] > comun[mejor]))
                mejor = i;
        }
        if (mejor == -1) break;             // no hay mas candidatos
        cout << "  " << vez + 1 << ". " << usuarios[mejor].getnombre_usuario()
             << " (" << comun[mejor] << " amigos en comun)" << endl;
        elegidos[cuantos] = mejor;
        cuantos++;
        comun[mejor] = 0;                   // para no elegirlo otra vez
    }

    if (cuantos > 0) {
        int op;
        cout << "Enviar solicitud a (numero, 0 = ninguno): ";
        cin >> op;
        if (op >= 1 && op <= cuantos)
            enviar_solicitud_a(elegidos[op - 1]);
    }

    delete[] comun;
    delete[] elegidos;
}

//memoria

long long udeabook::memoria_total()
{
    long long m = sizeof(*this);
    m += usuarios.getCapacidad() * (long long)sizeof(usuario);     //usuarios
    for (int i = 0; i < n; i++)
        m += usuarios[i].memoria_extra();                          // lo de cada usuario
    m += (long long)n * n * sizeof(bool);                          // la matriz
    m += mensajes.getCapacidad() * (long long)sizeof(mensaje);
    for (int i = 0; i < mensajes.gettamano(); i++)
        m += mensajes[i].memoria_extra();
    return m;
}

bool udeabook::cargar_mensajes(string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo) {
        cout << "No se pudo abrir " << nombre_archivo << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        memoria::contar();
        if (linea.empty()) continue;

        stringstream ss(linea);
        string se, sr, sf, sl, texto;
        getline(ss, se, ';');
        getline(ss, sr, ';');
        getline(ss, sf, ';');
        getline(ss, sl, ';');
        getline(ss, texto);                  // el resto de la linea es el texto
        int e = stoi(se);
        int r = stoi(sr);
        if (e < 0 || e >= n || r < 0 || r >= n) continue;

        mensaje m(e, r, stoll(sf), sl == "1", texto);
        int pos = mensajes.gettamano();      // la casa donde va a quedar
        mensajes.agregar(m);
        usuarios[e].agregar_enviado(pos);
        usuarios[r].agregar_recibido(pos);
    }
    archivo.close();
    return true;
}


long long udeabook::fecha_actual()
{
    time_t t = time(0);
    tm* f = localtime(&t);
    long long fecha = f->tm_year + 1900;
    fecha = fecha * 100 + (f->tm_mon + 1);
    fecha = fecha * 100 + f->tm_mday;
    fecha = fecha * 100 + f->tm_hour;
    fecha = fecha * 100 + f->tm_min;
    return fecha;
}

void udeabook::enviar_mensaje()
{
    string nombre;
    cout << "Para (nombre del amigo): ";
    cin >> nombre;
    int destino = buscar_usuario(nombre);
    if (destino == -1) {
        cout << "No existe ese usuario" << endl;
        return;
    }
    if (!matriz[actual * n + destino]) {
        cout << "Solo puedes escribirle a tus amigos" << endl;
        return;
    }

    string texto;
    cout << "Mensaje: ";
    cin.ignore();                            // quitar el Enter que dejo el cin >> anterior
    getline(cin, texto);
    if (texto.empty() || texto.size() > 512) {
        cout << "El mensaje debe tener entre 1 y 512 caracteres" << endl;
        return;
    }

    mensaje m(actual, destino, fecha_actual(), false, texto);
    cout << "paso 1" << endl;                       // agregar
    int pos = mensajes.gettamano();
    mensajes.agregar(m);
    cout << "paso 2" << endl;
    usuarios[actual].agregar_enviado(pos);
    usuarios[destino].agregar_recibido(pos);
    cout << "paso 3" << endl;
    cout << "Mensaje enviado a " << nombre << endl;
}

void udeabook::leer_nuevos()
{
    ArregloDinamico<int>& rec = usuarios[actual].getrecibidos();
    int nuevos = 0;
    for (int i = 0; i < rec.gettamano(); i++) {
        memoria::contar();
        mensaje& m = mensajes[rec[i]];       // el original, no una copia
        if (!m.getleido()) {
            cout << "  [" << m.getfecha() << "] " << usuarios[m.getemisor()].getnombre_usuario()
            << ": " << m.gettexto() << endl;
            m.marcar_leido();
            nuevos++;
        }
    }
    if (nuevos == 0)
        cout << "No tienes mensajes nuevos" << endl;
}

int udeabook::primero_desde(ArregloDinamico<int>& rec, long long desde)
{
    int ini = 0, fin = rec.gettamano() - 1;
    int resp = rec.gettamano();              // si ninguno cumple, queda al final
    while (ini <= fin) {
        memoria::contar();
        int medio = (ini + fin) / 2;
        if (mensajes[rec[medio]].getfecha() >= desde) {
            resp = medio;                    // sirve, pero puede haber uno antes
            fin = medio - 1;
        } else {
            ini = medio + 1;
        }
    }
    return resp;
}

void udeabook::buscar_mensajes()
{
    long long inicio, final_;
    cout << "Desde (AAAAMMDD): ";
    cin >> inicio;
    cout << "Hasta (AAAAMMDD): ";
    cin >> final_;
    if (inicio > final_) {
        cout << "La fecha inicial debe ser menor o igual a la final" << endl;
        return;
    }
    long long desde = inicio * 10000;
    long long hasta = final_ * 10000 + 2359;
    ArregloDinamico<int>& rec = usuarios[actual].getrecibidos();
    int i = primero_desde(rec, desde);
    int encontrados = 0;
    while (i < rec.gettamano() && mensajes[rec[i]].getfecha() <= hasta) {
        memoria::contar();
        mensaje& m = mensajes[rec[i]];
        cout << "  [" << m.getfecha() << "] " << usuarios[m.getemisor()].getnombre_usuario()
             << ": " << m.gettexto() << endl;
        encontrados++;
        i++;
    }
    cout << encontrados << " mensajes en ese rango" << endl;
}

void udeabook::guardar_datos()


    {
        // amistades: cada pareja una sola vez (solo cuando i < j)
        ofstream am("amistades.txt");
        for (int i = 0; i < n; i++) {
            ArregloDinamico<int>& amigos = usuarios[i].getamigos();
            for (int k = 0; k < amigos.gettamano(); k++) {
                memoria::contar();
                if (i < amigos[k])
                    am << i << ";" << amigos[k] << endl;
            }
        }
        am.close();

        // solicitudes emisor;receptor
        ofstream so("solicitudes.txt");
        for (int r = 0; r < n; r++) {
            ArregloDinamico<int>& sol = usuarios[r].getsolicitudes();
            for (int k = 0; k < sol.gettamano(); k++) {
                memoria::contar();
                so << sol[k] << ";" << r << endl;
            }
        }
        so.close();

        // mensajes  emisor;receptor;fecha;leido;texto
        ofstream me("mensajes.txt");
        for (int i = 0; i < mensajes.gettamano(); i++) {
            memoria::contar();
            mensaje& m = mensajes[i];
            me << m.getemisor() << ";" << m.getreceptor() << ";" << m.getfecha() << ";"
               << m.getleido() << ";" << m.gettexto() << endl;
        }
        me.close();

        cout << "Datos guardados" << endl;
    }
//fotos
    bool udeabook::cargar_albumes(string nombre_archivo)
    {
        ifstream archivo(nombre_archivo);
        if (!archivo) {
            cout << "No se pudo abrir " << nombre_archivo << endl;
            return false;
        }

        string linea;
        while (getline(archivo, linea)) {
            memoria::contar();
            if (linea.empty()) continue;

            stringstream ss(linea);
            string sd, nombre, sp;
            getline(ss, sd, ';');
            getline(ss, nombre, ';');
            getline(ss, sp, ';');
            int dueno = stoi(sd);
            if (dueno < 0 || dueno >= n) continue;

            album a(nombre, stoi(sp));
            usuarios[dueno].agregar_album(a);
        }
        archivo.close();
        return true;
    }

    //  Dueño;album;nombre;fecha;tamano;likes
    bool udeabook::cargar_fotos(string nombre_archivo)
    {
        ifstream archivo(nombre_archivo);
        if (!archivo) {
            cout << "No se pudo abrir " << nombre_archivo << endl;
            return false;
        }

        string linea;
        while (getline(archivo, linea)) {
            memoria::contar();
            if (linea.empty()) continue;

            stringstream ss(linea);
            string sd, sa, nombre, sf, st, sl;
            getline(ss, sd, ';');
            getline(ss, sa, ';');
            getline(ss, nombre, ';');
            getline(ss, sf, ';');
            getline(ss, st, ';');
            getline(ss, sl, ';');
            int dueno = stoi(sd);
            int a = stoi(sa);
            if (dueno < 0 || dueno >= n) continue;
            ArregloDinamico<album>& albs = usuarios[dueno].getalbumes();
            if (a < 0 || a >= albs.gettamano()) continue;

            foto f(nombre, stoi(sf), stoi(st), stoi(sl));
            albs[a].agregar_foto(f);          // la foto queda en el album
        }
        archivo.close();
        return true;
    }

    void udeabook::visitar_perfil()
    {
        string nombre;
        cout << "Nombre del amigo: ";
        cin >> nombre;
        int amigo = buscar_usuario(nombre);
        if (amigo == -1) {
            cout << "No existe ese usuario" << endl;
            return;
        }
        if (!matriz[actual * n + amigo]) {
            cout << "Solo puedes visitar el perfil de tus amigos" << endl;
            return;
        }


        ArregloDinamico<album>& albs = usuarios[amigo].getalbumes();
        int* visibles = new int[albs.gettamano() + 1];
        int cuantos = 0;
        cout << "Albumes de " << nombre << ":" << endl;
        for (int i = 0; i < albs.gettamano(); i++) {
            memoria::contar();
            if (albs[i].getprivacidad() != 2) {
                visibles[cuantos] = i;
                cuantos++;
                cout << "  " << cuantos << ". " << albs[i].getnombre()
                     << " (" << albs[i].getfotos().gettamano() << " fotos)" << endl;
            }
        }
        if (cuantos == 0) {
            cout << "No tiene albumes visibles" << endl;
            delete[] visibles;
            return;
        }

        int op;
        cout << "Album a ver (0 = ninguno): ";
        cin >> op;
        if (op >= 1 && op <= cuantos)
            carrusel(amigo, albs[visibles[op - 1]]);
        delete[] visibles;
    }


    void udeabook::carrusel(int dueno, album& alb)
    {
        ArregloDinamico<foto>& fotos = alb.getfotos();
        int total = fotos.gettamano();
        if (total == 0) {
            cout << "El album esta vacio" << endl;
            return;
        }

        string nombre = usuarios[dueno].getnombre_usuario();
        int pos = 0;
        char c = ' ';
        while (c != 'x') {
            memoria::contar();
            foto& f = fotos[pos];               // la original, para que el like quede
            cout << "\n[" << pos + 1 << "/" << total << "] /users/udeabook/" << nombre
                 << "/albums/" << alb.getnombre() << "/" << f.getnombre() << ".png" << endl;
            cout << "    Fecha: " << f.getfecha() << "   Tamano: " << f.gettamano() / 1024
                 << " KB   Likes: " << f.getlikes() << endl;
            cout << "s = siguiente, a = anterior, l = like, x = salir: ";
            cin >> c;

            if (c == 's')
                pos = (pos + 1) % total;            // de la ultima vuelve a la 0
            else if (c == 'a')
                pos = (pos - 1 + total) % total;    // +total para no dar negativo
            else if (c == 'l') {
                f.dar_like();
                cout << "Te gusta esta foto" << endl;
            }
        }
    }
