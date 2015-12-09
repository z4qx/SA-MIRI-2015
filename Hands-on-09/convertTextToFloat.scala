import org.apache.spark.mllib.linalg.Vectors
val parsedData = data.map(s =>Vectors.dense(s.split(" ").map(_.toDouble))).cache()
parsedData.foreach(println)
