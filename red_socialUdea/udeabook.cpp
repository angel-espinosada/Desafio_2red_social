#include "udeabook.h"
#include "memoria.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


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

// ---------------- I. Carga de datos ----------------

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

// ---------------- III. Administrar amistades ----------------

// true si 'de' ya le envio una solicitud a 'para'
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

// ---------------- V. Sugerencias de amistad ----------------

// Candidatos = amigos de mis amigos. Si recorro los amigos de cada amigo y sumo 1
// cada vez que aparece alguien, ese contador es exactamente los amigos en comun.
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

    // elegir los k mayores: buscar el maximo k veces
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

// ---------------- VII. Memoria ----------------

long long udeabook::memoria_total()
{
    long long m = sizeof(*this);                                   // el objeto red
    m += usuarios.getCapacidad() * (long long)sizeof(usuario);     // casas de usuarios
    for (int i = 0; i < n; i++)
        m += usuarios[i].memoria_extra();                          // lo de cada usuario
    m += (long long)n * n * sizeof(bool);                          // la matriz
    return m;
}
