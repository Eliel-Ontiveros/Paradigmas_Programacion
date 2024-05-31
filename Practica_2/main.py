from Sistema_Bancario import SistemaBancario

sistema_bancario = SistemaBancario()

while True:
    print("\nMenu:")
    print("1. Iniciar sesión")
    print("2. Crear nueva cuenta")
    print("3. Salir")
    opcion = input("Seleccione una opcion: ")

    if opcion == "1":
        numero_cuenta = int(input("Ingrese su numero de cuenta: "))
        pin = input("Ingrese su PIN: ")
        cliente = sistema_bancario.iniciar_sesion(numero_cuenta, pin)
        if cliente:
            while True:
                print("\nOpciones disponibles:")
                print("1. Consultar Saldo")
                print("2. Transferir a otros usuarios")
                print("3. Retirar dinero")
                print("4. Depositar dinero")
                print("0. Volver al menu principal")
                accion = input("Seleccione una accion: ")

                if accion == "1":
                    cliente.consultar_saldo()
                elif accion == "2":
                    cuenta_destino = int(input("Ingrese el numero de cuenta destino: "))
                    monto = float(input("Ingrese el monto a transferir: "))
                    if sistema_bancario.iniciar_sesion(numero_cuenta, pin): 
                        cuenta_destino_obj = sistema_bancario.clientes.get(cuenta_destino)
                        if cuenta_destino_obj:
                            cliente.transferir(cuenta_destino_obj, monto)
                        else:
                            print("Numero de cuenta destino no valido.")
                    else:
                        print("PIN incorrecto.")
                elif accion == "3":
                    monto = float(input("Ingrese el monto a retirar: "))
                    cliente.retirar(monto)
                elif accion == "4":
                    monto = float(input("Ingrese el monto a depositar: "))
                    cliente.depositar(monto)
                elif accion == "0":
                    break
                else:
                    print("Accion no valida.")

    elif opcion == "2":
        nombre = input("Ingrese su nombre: ")
        sistema_bancario.registrar_cliente(nombre)

    elif opcion == "3":
        print("¡Hasta luego!")
        break

    else:
        print("Opcion no valida. Intente nuevamente.")
