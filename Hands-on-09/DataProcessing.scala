val documents = sc.textFile("example2.txt").map(_.split(" ").toSeq)
documents.foreach(println)
