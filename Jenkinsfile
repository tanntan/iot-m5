pipeline {
  agent any
  stages {
    stage('install pyelftools') {
      parallel {
        stage('install pyelftools') {
          steps {
            sh 'pip3 install pyelftools'
          }
        }

        stage('install platformio') {
          steps {
            sh 'pip3 install platformio'
          }
        }

      }
    }

    stage('') {
      steps {
        sh 'pio run'
      }
    }

  }
}