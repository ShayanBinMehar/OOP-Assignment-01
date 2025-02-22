#include <iostream>
#include <string>

using namespace std;

class Player {
public:
    string alias;
    int score;

    Player(const string& alias) : alias(alias), score(0) {}

    void moveBall(int& posX, int& posY, const string& moveDir) {
        if (moveDir == "up") {
            posY++;
        } else if (moveDir == "down") {
            posY--;
        } else if (moveDir == "left") {
            posX--;
        } else if (moveDir == "right") {
            posX++;
        }
        score++;
    }
};

class Sphere {
private:
    int coordX;
    int coordY;

public:
    Sphere(int x, int y) : coordX(x), coordY(y) {}

    int getX() const { return coordX; }
    int getY() const { return coordY; }

    void shift(int dx, int dy) {
        coordX += dx;
        coordY += dy;
    }
};

class Target {
private:
    int locX;
    int locY;

public:
    Target(int x, int y) : locX(x), locY(y) {}

    bool reached(int ballX, int ballY) const {
        return (ballX == locX && ballY == locY);
    }
};

class Squad {
public:
    string squadName;
    Player* player;

    Squad(const string& squadName, Player* player) : squadName(squadName), player(player) {}
};

class Match {
public:
    Squad squadOne;
    Squad squadTwo;
    Sphere sphere;
    Target target;

    Match(const Squad& s1, const Squad& s2, const Sphere& sp, const Target& tg)
        : squadOne(s1), squadTwo(s2), sphere(sp), target(tg) {}

    void beginMatch() {
        executeMove(&squadOne);
        executeMove(&squadTwo);
        announceWinner();
    }

    void executeMove(Squad* squad) {
        cout << "Squad " << squad->squadName << "'s move:" << endl;
        int posX = sphere.getX();
        int posY = sphere.getY();
        while (!target.reached(posX, posY)) {
            string moveDir;
            cout << "Move " << squad->player->alias << " (up, down, left, right): ";
            cin >> moveDir;
            squad->player->moveBall(posX, posY, moveDir);
            sphere.shift(posX - sphere.getX(), posY - sphere.getY());
            cout << "Current ball position: (" << posX << ", " << posY << ")" << endl;
        }
        cout << squad->player->alias << " reached the target in " << squad->player->score << " moves." << endl;
    }

    void announceWinner() {
        if (squadOne.player->score < squadTwo.player->score) {
            cout << "Squad " << squadOne.squadName << " wins!" << endl;
        } else if (squadTwo.player->score < squadOne.player->score) {
            cout << "Squad " << squadTwo.squadName << " wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }
    }
};

int main() {
    Player p1("Alpha");
    Player p2("Beta");
    Squad team1("Titans", &p1);
    Squad team2("Warriors", &p2);
    Sphere ball(0, 0);
    Target goal(3, 3);

    Match game(team1, team2, ball, goal);
    game.beginMatch();

    return 0;
}
