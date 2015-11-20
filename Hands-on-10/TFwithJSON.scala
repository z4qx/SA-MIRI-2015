val sqlContext = new org.apache.spark.sql.SQLContext(sc)
val photos = sqlContext.jsonFile("example3.txt")
photos.printSchema
photos.count
photos.registerTempTable("pt")
val tags = sqlContext.sql("select tags from pt where tags is not null")
tags.collect.foreach(println)
val tagsAsArray = tags.map(aRow => aRow(0).asInstanceOf[scala.collection.mutable.ArrayBuffer[String]])
tagsAsArray.collect.foreach(println)


