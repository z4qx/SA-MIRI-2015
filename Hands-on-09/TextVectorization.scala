import org.apache.spark.rdd.RDD
import org.apache.spark.mllib.feature.HashingTF
val hashingTF = new HashingTF()
val tf = hashingTF.transform(documents)
tf.foreach(println)

