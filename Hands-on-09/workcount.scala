val file = sc.textFile("README.md")
val counts = file.flatMap( line => line.split(" ")).map(word => (word, 1)).reduceByKey(_ + _)
counts.saveAsTextFile("wc_out")

