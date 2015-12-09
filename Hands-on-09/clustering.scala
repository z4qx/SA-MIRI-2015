import org.apache.spark.mllib.clustering.KMeans
val clusters = KMeans.train(tf, 2, 1)
val results = documents.map(x => Vector(x, clusters.predict(hashingTF.transform(x)))) 
results.collect.foreach(println)

