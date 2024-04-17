#include <iostream>
#include <cmath>
#include <climits>
#include <bitset>

using namespace std;

// Función para multiplicar dos números en formato de punto flotante y mostrar el resultado en binario
void multiplicacion(float num1, float num2) {
    int bias = (1 << 7) - 1;
    // Unión para acceder a los bits de los números en punto flotante
    union {
        float flotante;
        int bits;
    }numero1, numero2, resultado;

    numero1.flotante = num1;
    numero2.flotante = num2;
    //Extraer los componentes (signo, exponente y significando)
    int signo1 = (numero1.bits >> 31) & 1;
    int signo2 = (numero2.bits >> 31) & 1;
    int exponente1 = ((numero1.bits >> 23) & ((1 << 8) - 1)) - bias;
    int exponente2 = ((numero2.bits >> 23) & ((1 << 8) - 1)) - bias;
    int significando1 = (numero1.bits & ((1 << 23) - 1)) | (1 << 23);
    int significando2 = (numero2.bits & ((1 << 23) - 1)) | (1 << 23);

    long long producto = static_cast<long long>(significando1) * significando2;
    int exponente_resultado = exponente1 + exponente2 + bias;

    if(producto & (1LL<<47))
    {
        producto >>= 1;
        exponente_resultado++;
    }
    if(exponente_resultado > ((1<<8) - 1))
    {
        resultado.bits = (signo1^signo2) << 31 | ((1<<8) - 1) << 23;
    }
    else if(exponente_resultado < 0) 
    {
        resultado.bits = (signo1^signo2) << 31;
    }
    else
    {
        resultado.bits = (signo1^signo2) << 31 | (exponente_resultado+bias) << 23 | ((producto>>24) & ((1<<23) - 1));
    }
    int resultado_binario = resultado.bits;
    cout << "Resultado en binario:" <<bitset<23>(resultado_binario)<<endl;
}

int main(){
    float num1, num2;
    cout<<"Digite un numero flotante: ";
    cin>>num1;
    cout<<"Digite otro numero flotante: ";
    cin>>num2;

    multiplicacion(num1,num2);

    return 0;
}
