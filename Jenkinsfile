pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        echo 'Hello'
        sh 'iot/pio run -d ./apps/ltie-ltm-tls2.0-integration/ -e release'
      }
    }

  }
}