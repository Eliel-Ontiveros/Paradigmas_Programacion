from Cuenta_Bancaria import CuentaBancaria

class SistemaBancario:
    def __init__(self):
        self.clientes = {}
        self.numero_cuenta_actual = 1000 

    def registrar_cliente(self, nombre):
        pin = input("Elija un PIN para su cuenta: ")
        self.numero_cuenta_actual += 1
        numero_cuenta = self.numero_cuenta_actual
        cuenta_bancaria = CuentaBancaria(numero_cuenta, 0, "Corriente", pin)
        self.clientes[numero_cuenta] = cuenta_bancaria
        print(f"Cuenta creada para {nombre}. Numero de cuenta: {numero_cuenta}")
        return cuenta_bancaria

    def iniciar_sesion(self, numero_cuenta, pin):
        if numero_cuenta in self.clientes and self.clientes[numero_cuenta].pin == pin:
            return self.clientes[numero_cuenta]
        else:
            print("Numero de cuenta no valido o PIN incorrecto.")
            return None
