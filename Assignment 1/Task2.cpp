#include <iostream>
#include <string>
using namespace std;

class Ball;

class Robot {
    string name;
    int hits;

public:
    Robot(string name) : name(name), hits(0) {}

    void hitBall(Ball &ball, const string &direction);

    string get_name() {
        return name;
    }

    int get_hits() {
        return hits;
    }
};

class Ball {
    int X;
    int Y;

public:
    void setBallPoints(int initial_X = 0, int initial_Y = 0) {
        X = initial_X;
        Y = initial_Y;
    }

    int get_X() {
        return X;
    }

    int get_Y() {
        return Y;
    }

    pair<int, int> getPosition() {
        return make_pair(X, Y);
    }
};

void Robot::hitBall(Ball &ball, const string &direction) {
    int ballX = ball.get_X();
    int ballY = ball.get_Y();

    if (direction == "UP") {
        ballY++;
    } else if (direction == "DOWN") {
        ballY--;
    } else if (direction == "LEFT") {
        ballX--;
    } else if (direction == "RIGHT") {
        ballX++;
    }

    ball.setBallPoints(ballX, ballY);
    hits++;
}

class Goal {
    int x;
    int y;

public:
    Goal(int x = 3, int y = 3) {
        this->x = x;
        this->y = y;
    }

    bool isGoalReached(int X, int Y) {
        return (X == x && Y == y); 
    }
};

class Team {
    string teamName;
    Robot* R1;

public:
    Team(string teamName, Robot* R1) {
        this->teamName = teamName;
        this->R1 = R1;
    }

    string get_teamName() {
        return teamName;
    }

    Robot* get_robot() { 
        return R1;
    }
};

class Game {
    Team* teamOne;
    Team* teamTwo;
    Goal goalObj;
    Ball ballObj;

public:
    Game(Team* teamOne, Team* teamTwo) {
        this->teamOne = teamOne;
        this->teamTwo = teamTwo;
        ballObj.setBallPoints(0, 0);
    }

    void play(Team *team) {
        Robot* R1 = team->get_robot();
        cout << "Team " << team->get_teamName() << "'s Turn..." << endl;

        while (!goalObj.isGoalReached(ballObj.get_X(), ballObj.get_Y())) {
            string direction;
            cout << "Enter direction of robot (UP, DOWN, LEFT, RIGHT): ";
            cin >> direction;

            if (direction != "UP" && direction != "DOWN" && direction != "LEFT" && direction != "RIGHT") {
                cout << "Invalid direction! Please enter UP, DOWN, LEFT, or RIGHT." << endl;
                continue;
            }
            R1->hitBall(ballObj, direction);

            // Display the new ball position
            cout << "The ball Position is: (" << ballObj.get_X() << ", " << ballObj.get_Y() << ")" << endl;
        }
        cout << "The team " << team->get_teamName() << " finally reached their goal in " << R1->get_hits() << " hits" << endl;
    }

    void startGame() {
        cout << "Start the game..." << endl;
        while (!goalObj.isGoalReached(ballObj.get_X(), ballObj.get_Y())) {
            play(teamOne);
            if (goalObj.isGoalReached(ballObj.get_X(), ballObj.get_Y())) break;
            play(teamTwo);
        }
        declareWinner();
    }

    void declareWinner() {
        int teamOneHits = teamOne->get_robot()->get_hits();
        int teamTwoHits = teamTwo->get_robot()->get_hits();

        cout << "Final results are below..." << endl;
        cout << "The team " << teamOne->get_teamName() << " hits: " << teamOneHits << endl;
        cout << "The team " << teamTwo->get_teamName() << " hits: " << teamTwoHits << endl;

        if (teamOneHits < teamTwoHits) {
            cout << "Team " << teamOne->get_teamName() << " wins" << endl;
        } else if (teamOneHits > teamTwoHits) {
            cout << "Team " << teamTwo->get_teamName() << " wins" << endl;
        } else {
            cout << "It is a Tie!!!" << endl;
        }
    }
};

int main() {
    Robot robot1("RoboKicker");
    Robot robot2("GoalMaster");

    Team team1("Team A", &robot1);
    Team team2("Team B", &robot2);

    Game game(&team1, &team2);
    game.startGame();

    return 0;
}
