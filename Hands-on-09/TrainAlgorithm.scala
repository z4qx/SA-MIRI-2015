import org.apache.spark.mllib.clustering.KMeans
// Build the model (cluster the data)
val clusters = KMeans.train(parsedData, 5, 10)
# Evaluate clustering by computing Within Set Sum of Squared Errors
val WSSSE = clusters.computeCost(parsedData)
print("Within Set Sum of Squared Error = " + WSSSE)
