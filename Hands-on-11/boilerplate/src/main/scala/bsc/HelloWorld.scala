package com.examples;
import org.apache.spark.SparkContext
import org.apache.spark.SparkContext._
import org.apache.spark.SparkConf
object Helloworld {
 def main(arg: Array[String]) {
      val conf = new SparkConf().setAppName("Simple Wordcount")  
      val sc = new SparkContext(conf)
      //Your Spark code goes here
      val input ="/home/sam14/sam14030/datasets/dataset.txt"
	val output_dir = "/home/sam14/sam14030/wordcount" 
	val logData = sc.textFile(input, 2).cache()
	val count = logData.flatMap(line => line.split(" "))
             	.map(word => (word, 1))
             	.reduceByKey(_ + _)
	count.saveAsTextFile(output_dir) 
   }
}

