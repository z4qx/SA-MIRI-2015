val hashingTF = new HashingTF()
val tf = hashingTF.transform(tagsAsArray)
tf.foreach(println)
val clusters = KMeans.train(tf, 2, 1)
val results = documents.map(x => Vector(x, clusters.predict(hashingTF.transform(x)))) 
results.collect.foreach(println)
