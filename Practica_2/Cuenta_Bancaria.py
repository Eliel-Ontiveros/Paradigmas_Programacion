class CuentaBancaria:
    def __init__(self, numero_cuenta, saldo, tipo_cuenta, pin):
        self.numero_cuenta = numero_cuenta
        self.saldo = saldo
        self.tipo_cuenta = tipo_cuenta
        self.pin = pin

    def depositar(self, monto):
        if monto > 0:
            self.saldo += monto
            print(f"Deposito exitoso. Saldo actual: {self.saldo}")
        else:
            print("El monto debe ser mayor que cero.")

    def retirar(self, monto):
        if monto > 0 and monto <= self.saldo:
            self.saldo -= monto
            print(f"Retiro exitoso. Saldo actual: {self.saldo}")
            return True
        else:
            print("Monto invalido o saldo insuficiente.")
            return False

    def consultar_saldo(self):
        print(f"Saldo actual: {self.saldo}")

    def transferir(self, cuenta_destino, monto):
        if cuenta_destino and self.retirar(monto):
            cuenta_destino.depositar(monto)
            print(f"Transferencia de {monto} al numero de cuenta {cuenta_destino.numero_cuenta} completada.")
        else:
            print("Transferencia fallida. Verifique los datos y el saldo.")
