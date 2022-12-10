import scala.io.Source

type Command = (Int, Int)

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

def run(commands: List[Command]): Unit =
  val check = 40

  def run(commands: List[Command], cpu: Int, acc: String): Unit =
    if (commands.isEmpty) {
      return
    }

    val sprite = if (cpu until (cpu + 3) contains acc.length + 1) { "#" } else { "." }
    val buffer = acc + sprite

    def handle_buffer_flush(commands: List[Command], cpu: Int, buffer: String): Unit =
      println(buffer)
      run(commands, cpu, "")

    val command = commands.head

    if (command(0) - 1 == 0) {
      val register = cpu + command(1)

      if (buffer.length == check) {
        handle_buffer_flush(commands.tail, register, buffer)
      }

      run(commands.tail, register, buffer)
    } else {
      var next_commands = (command(0) - 1, command(1)) :: commands.tail

      if (buffer.length == check) {
        handle_buffer_flush(next_commands, cpu, buffer)
      }

      run(next_commands, cpu, buffer)
    }

  val cpu = 1
  run(commands, cpu, "")

@main def main(path: String, others: String*): Unit = 
  val input = loadFile(path)
  run(input)

