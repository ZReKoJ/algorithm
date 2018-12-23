// E26, Zihao Hong
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstddef>    // size_t
#include <stdexcept>  // std::domain_error
#include <utility>    // std::move
#include <math.h>
#include <climits>
#include <map>
#include <set>
#include <utility>

#ifndef DOMJUDGE
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
#endif

class Fecha {
private:
	int dia, hora, minuto;
public:
	Fecha() {}
	Fecha(int d, int h, int m) {
		if ((0 <= d && d < 31) && (0 <= h && h < 24) && (0 <= m && m < 60)) {
			dia = d; hora = h; minuto = m;
		}
		else throw std::domain_error("ERROR");
	}

	int getD() const& {
		return dia;
	}

	int getH() const& {
		return hora;
	}

	int getM() const& {
		return minuto;
	}

	bool operator<= (const Fecha &that) const {
		if (dia == that.dia) {
			if (hora == that.hora) return minuto <= that.minuto;
			else return hora < that.hora;
		}
		else return dia < that.dia;
	}
	bool operator< (const Fecha &that) const {
		if (dia == that.dia) {
			if (hora == that.hora) return minuto < that.minuto;
			else return hora < that.hora;
		}
		else return dia < that.dia;
	}
	bool operator== (const Fecha &that) const {
		return (dia == that.dia && hora == that.hora && minuto == that.minuto);
	}
};


struct info {
	std::string medico;
	std::string paciente;
	Fecha fecha;
	info(std::string const& m, std::string const& p, Fecha const& f) : medico(m), paciente(p), fecha(f) {}
};

class Consultorio {
protected:
	std::map<std::string, std::map<Fecha, info>> doctores;
public:
	Consultorio() {}

	void nuevoMedico(std::string const& medico) {
		if (doctores.count(medico) == 0) {
			std::map<Fecha, info> citas;
			doctores.insert(std::pair<std::string, std::map<Fecha, info>>(medico, citas));
		}
	}

	void pideConsulta(std::string const& paciente, std::string const& medico, Fecha const& fecha) {
		if (doctores.count(medico) == 0)  throw std::domain_error("Medico no existente\n");
		else {
			bool found = false;
			std::pair<std::multimap<Fecha, info>::iterator, std::multimap<Fecha, info>::iterator> p;
			if (doctores[medico].count(fecha) == 0) {
				doctores[medico].insert(std::pair<Fecha, info>(fecha, info(medico, paciente, fecha)));
			}
			else throw std::domain_error("Fecha ocupada\n");
		}
	}

	info siguientePaciente(std::string const& medico) {
		if (doctores.count(medico) == 0)  throw std::domain_error("Medico no existente\n");
		else {
			if (doctores.at(medico).size() == 0) throw std::domain_error("No hay pacientes\n");
			else {
				std::map<Fecha, info>::iterator it = doctores[medico].begin();
				return it->second;
			}
		}
	}

	void atiendeConsulta(std::string const& medico) {
		if (doctores.count(medico) == 0)  throw std::domain_error("Medico no existente\n");
		else {
			if (doctores.at(medico).size() == 0) throw std::domain_error("No hay pacientes\n");
			else {
				std::map<Fecha, info>::iterator it = doctores[medico].begin();
				doctores[medico].erase(it);
			}
		}
	}

	std::vector<info> listaPacientes(std::string const& medico, int const& dia) {
		if (doctores.count(medico) == 0)  throw std::domain_error("Medico no existente\n");
		else {
			std::vector<info> f;
			for (std::multimap<Fecha, info>::iterator it = doctores[medico].begin(); it != doctores[medico].end(); ++it) {
				if (it->second.fecha.getD() == dia) f.emplace_back(it->second);
			}
			return f;
		}
	}
};

bool resuelveCaso() {
	int numCasos;
	std::cin >> numCasos;
	if (!std::cin.fail()) {
		Consultorio c;
		std::string caso, medico, paciente;
		int dia, hora, minuto;
		for (int i = 0; i < numCasos; ++i) {
			try {
				std::cin >> caso;
				if (caso == "nuevoMedico") {
					std::cin >> medico;
					c.nuevoMedico(medico);
				}
				else if (caso == "pideConsulta") {
					std::cin >> paciente >> medico >> dia >> hora >> minuto;
					c.pideConsulta(paciente, medico, Fecha(dia, hora, minuto));
				}
				else if (caso == "siguientePaciente") {
					std::cin >> medico;
					info sigP = c.siguientePaciente(medico);
					std::cout << "Siguiente Paciente doctor " << sigP.medico << "\n" << sigP.paciente << "\n---\n";
				}
				else if (caso == "atiendeConsulta") {
					std::cin >> medico;
					c.atiendeConsulta(medico);
				}
				else if (caso == "listaPacientes") {
					std::cin >> medico >> dia;
					std::vector<info> inf = c.listaPacientes(medico, dia);
					std::cout << "Doctor " << medico << " dia " << dia << "\n";
					if (inf.size() == 0) std::cout << "\n---\n";
					else {
						for (int i = 0; i < inf.size(); ++i) {
							std::cout << inf[i].paciente << " " << std::setfill('0') << std::setw(2) << inf[i].fecha.getH() << ":" << std::setw(2) << inf[i].fecha.getM() << "\n";
						}
						std::cout << "---\n";
					}
				}
				else {}
			}
			catch (std::domain_error &err) {
				std::cout << err.what() << "---\n";
			}
		}
		std::cout << "------\n";
		return true;
	}
	else return false;
}

int main() {
#ifndef DOMJUDGE
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::ifstream in("D:/Processing/C++/El Juez/El Juez/datosJuez.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	clock_t t = clock();
#endif 

	while (resuelveCaso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	t = clock() - t;
	std::cout << ((float)t / CLOCKS_PER_SEC) << '\n';
	system("PAUSE");
#endif

	return 0;
}