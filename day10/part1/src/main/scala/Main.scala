import scala.io.Source

type Command = (Int, Int)
type Cpu = (Int, Int)

def parse(line: String): Command =
  val command = line.split(" ").toList

  command(0) match
    case "noop" => (1, 0)
    case "addx" => (2, command(1).toInt)
    case _      => throw new Exception("Unknown command")

def loadFile(path: String): List[Command] =
  val file = Source.fromFile(path)
  val output = file.getLines().map(parse).toList

  file.close

  output

def run(commands: List[Command]): Int =
  val first_check = 20

  def run(commands: List[Command], cpu: Cpu, next_check: Int, acc: Int) : Int =
    if (commands.isEmpty) {
      return acc
    }

    val command = commands.head

    val cycles = cpu(0) + command(0)
    val register = cpu(1) + command(1)

    if (cycles > next_check) {
      val signal_strength = next_check * cpu(1)
      return run(commands.tail, (cycles, register), next_check + 40, acc + signal_strength)
    }

    run(commands.tail, (cycles, register), next_check, acc)

  val cpu = (1, 1)
  run(commands, cpu, first_check, 0)

@main def main(path: String, others: String*): Unit = 
  val input = loadFile(path)
  val result = run(input)

  println(result)
