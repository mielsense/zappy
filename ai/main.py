import argparse
from ai import Ai


def parse_arguments():
    parser = argparse.ArgumentParser(description='Zappy AI',
                                     usage='USAGE: ./zappy_ai -p port -n name -h machine\n'
                                           'option description\n'
                                           '-p port -n name -h machine port number name of the team name of the '
                                           'machine; localhost by default',
                                     add_help=False)

    parser.add_argument('-p', '--port', type=int,
                        required=True, help='Port number')
    parser.add_argument('-n', '--name', type=str,
                        required=True, help='Name of the team')
    parser.add_argument('-h', '--hostname', type=str, default='localhost',
                        help='Name of the machine; localhost by default')
    parser.add_argument('--help', action='help', default=argparse.SUPPRESS,
                        help='Show this help message and exit')
    return parser.parse_args()


def main():
    args = parse_arguments()
    server_address = args.hostname
    server_port = args.port
    team_name = args.name

    ai = Ai(server_address, server_port, team_name)
    ai.algorithm()
    ai.close()


if __name__ == "__main__":
    main()
