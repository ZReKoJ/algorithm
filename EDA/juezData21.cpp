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
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <list>

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

class iPud {
protected:
	struct cancionData {
		std::string nombre;
		std::string artista;
		int duracion;
		std::list<cancionData*>::iterator pl;
		std::list<std::string>::iterator h;
		std::map<std::string, std::list<cancionData*>::iterator> its;
	};
	std::unordered_map<std::string, cancionData*> songList;
	std::map<std::string, std::list<cancionData*>> artistList;
	struct playList {
		std::list<cancionData*> list;
		int totalTime = 0;
	};
	std::map<std::string, playList> playlists;
	playList playlist;
	std::list<std::string> history;
public:
	iPud() {}
	void addSong(std::string const& S, std::string const& A, int const& D) {
		if (songList.count(S) != 0) throw std::domain_error("ERROR ");
		else {
			cancionData *c = new cancionData{ S, A, D, playlist.list.end(), history.end() };
			songList[S] = c;
			artistList[A].emplace_back(c);
		}
	}

	void addToPlayList(std::string const& S) {
		if (songList.count(S) == 0) throw std::domain_error("ERROR ");
		else {
			cancionData *c = songList[S];
			if (c->pl == playlist.list.end()) {
				playlist.list.push_front(c);
				c->pl = playlist.list.begin();
				playlist.totalTime += c->duracion;
			}
		}
	}

	std::string current() {
		if (playlist.list.size() == 0) throw std::domain_error("ERROR ");
		else return playlist.list.back()->nombre;
	}

	std::string play() {
		if (playlist.list.size() == 0) return "No hay canciones en la lista";
		else {
			cancionData *c = playlist.list.back();
			playlist.list.erase(c->pl);
			playlist.totalTime -= c->duracion;
			c->pl = playlist.list.end();
			if (c->h != history.end()) history.erase(c->h);
			history.push_front(c->nombre);
			c->h = history.begin();
			return c->nombre;
		}
	}

	int totalTime() {
		return playlist.totalTime;
	}

	std::vector<std::string> recent(int const& n) {
		std::vector<std::string> v;
		int i = 0;
		std::list<std::string>::iterator it = history.begin();
		while (i < n && it != history.end()) {
			v.emplace_back(*it);
			++i;
			++it;
		}
		return v;
	}

	void deleteSong(std::string const& S) {
		if (songList.count(S) != 0) {
			cancionData *c = songList[S];
			if (c->pl != playlist.list.end()) {
				playlist.list.erase(c->pl);
				playlist.totalTime -= c->duracion;
			}
			if (c->h != history.end()) {
				history.erase(c->h);
			}
			for (std::map<std::string, std::list<cancionData*>::iterator>::iterator it = c->its.begin(); it != c->its.end(); ++it) {
				playlists[it->first].totalTime -= c->duracion;
				playlists[it->first].list.erase(it->second);
			}
			delete c;
			songList.erase(S);
		}
	}

	void saveCurrentList(std::string const& nombre) {
		playList *pl = &playlists[nombre];
		pl->list.clear();
		for (std::list<cancionData*>::reverse_iterator it = playlist.list.rbegin(); it != playlist.list.rend(); ++it) {
			pl->list.emplace_front(*it);
			(*it)->its[nombre] = pl->list.begin();
		}
		pl->totalTime = playlist.totalTime;
	}

	void generateArtistList(std::string const& artist) {
		playList *pl = &playlists[artist];
		pl->list.clear();
		std::list<cancionData*> art = artistList[artist];
		for (std::list<cancionData*>::reverse_iterator it = art.rbegin(); it != art.rend(); ++it) {
			pl->list.emplace_back(*it);
			(*it)->its[artist] = pl->list.begin();
			pl->totalTime += (*it)->duracion;
		}
	}

	void setPlayList(std::string const& nombre) {
		if (playlists.count(nombre) == 0) throw std::domain_error("ERROR ");
		else {
			playList *pl = &playlists[nombre];
			playlist.list.clear();
			for (std::list<cancionData*>::reverse_iterator it = pl->list.rbegin(); it != pl->list.rend(); ++it) {
				playlist.list.emplace_front(*it);
				(*it)->pl = playlist.list.begin();
			}
			playlist.totalTime = pl->totalTime;
		}
	}

	std::vector<std::string> allLists() {
		std::vector<std::string> v;
		for (std::map<std::string, playList>::iterator it = playlists.begin(); it != playlists.end(); ++it) {
			v.emplace_back(it->first);
		}
		return v;
	}

	~iPud() {
		for (std::unordered_map<std::string, cancionData *>::iterator it = songList.begin(); it != songList.end(); ++it) {
			delete it->second;
		}
	}
};

bool resuelveCaso() {
	std::string caso;
	std::cin >> caso;
	if (!std::cin.fail()) {
		iPud pud;
		std::string cancion, artista, nombre;
		int duracion, n;
		while (caso != "FIN") {
			try {
				if (caso == "addSong") {
					std::cin >> cancion >> artista >> duracion;
					pud.addSong(cancion, artista, duracion);
				}
				else if (caso == "addToPlaylist") {
					std::cin >> cancion;
					pud.addToPlayList(cancion);
				}
				else if (caso == "current") {
					pud.current();
				}
				else if (caso == "play") {
					std::string out = pud.play();
					if (out == "No hay canciones en la lista") std::cout << out << "\n";
					else std::cout << "Sonando " << out << "\n";
				}
				else if (caso == "totalTime") {
					std::cout << "Tiempo total " << pud.totalTime() << "\n";
				}
				else if (caso == "recent") {
					std::cin >> n;
					std::vector<std::string> v = pud.recent(n);
					if (v.size() == 0) std::cout << "No hay canciones recientes\n";
					else {
						std::cout << "Las " << n << " mas recientes\n";
						for (int i = 0; i < v.size(); ++i)
							std::cout << "    " << v[i] << "\n";
					}
				}
				else if (caso == "deleteSong") {
					std::cin >> cancion;
					pud.deleteSong(cancion);
				}
				else if (caso == "saveCurrentList") {
					std::cin >> nombre;
					pud.saveCurrentList(nombre);
				}
				else if (caso == "generateArtistList") {
					std::cin >> artista;
					pud.generateArtistList(artista);
				}
				else if (caso == "setPlaylist") {
					std::cin >> nombre;
					pud.setPlayList(nombre);
				}
				else if (caso == "allLists") {
					std::vector<std::string> v = pud.allLists();
					if (v.size() == 0) std::cout << "No hay listas de reproduccion\n";
					else {
						std::cout << " Listas de reproduccion\n";
						for (int i = 0; i < v.size(); ++i)
							std::cout << "    " << v[i] << "\n";
					}
				}
				else {
					int a = 0;
				}
			}
			catch (std::domain_error &err) {
				std::cout << err.what() << caso << "\n";
			}
			std::cin >> caso;
		}
		std::cout << "----\n";
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